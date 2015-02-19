/*
 * (C) 2006-2015 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "stdafx.h"
#include "DXVA1DecoderMPEG2.h"
#include "../MPCVideoDec.h"
#include "../FfmpegContext.h"
#include "FfmpegContext_DXVA1.h"
#include <ffmpeg/libavcodec/avcodec.h>

#if 0
	#define TRACE_MPEG2 TRACE
#else
	#define TRACE_MPEG2 __noop
#endif

CDXVA1DecoderMPEG2::CDXVA1DecoderMPEG2(CMPCVideoDecFilter* pFilter, IAMVideoAccelerator*  pAMVideoAccelerator, int nPicEntryNumber)
	: CDXVA1Decoder(pFilter, pAMVideoAccelerator, nPicEntryNumber)
{
	memset(&m_PictureParams, 0, sizeof(m_PictureParams));
	memset(&m_SliceInfo, 0, sizeof(m_SliceInfo));
	memset(&m_QMatrixData, 0, sizeof(m_QMatrixData));

	m_PictureParams.bMacroblockWidthMinus1	= 15;
	m_PictureParams.bMacroblockHeightMinus1	= 15;
	m_PictureParams.bBlockWidthMinus1		= 7;
	m_PictureParams.bBlockHeightMinus1		= 7;
	m_PictureParams.bBPPminus1				= 7;
	m_PictureParams.bChromaFormat			= 1;

	m_nMaxWaiting			= 5;
	m_nSliceCount			= 0;

	Flush();
}

static CString FrameType(bool bIsField, BYTE bSecondField)
{
	CString str;
	if (bIsField) {
		str.Format(L"Field [%d]", bSecondField);
	} else {
		str = L"Frame";
	}

	return str;
}

HRESULT CDXVA1DecoderMPEG2::DecodeFrame(BYTE* pDataIn, UINT nSize, REFERENCE_TIME rtStart, REFERENCE_TIME rtStop)
{
	HRESULT	hr				= S_FALSE;
	int		nSurfaceIndex	= -1;
	bool	bIsField		= false;

	CHECK_HR_FALSE (FFMpeg2DecodeFrame(&m_PictureParams, &m_QMatrixData, m_SliceInfo,
									   m_pFilter->GetAVCtx(), m_pFilter->GetFrame(), pDataIn, nSize,
									   &m_nSliceCount, &m_nNextCodecIndex,
									   &bIsField));

	// Wait I frame after a flush
	if (m_bFlushed && (!m_PictureParams.bPicIntra || (bIsField && m_PictureParams.bSecondField))) {
		TRACE_MPEG2 ("CDXVA1DecoderMPEG2::DecodeFrame() : Flush - wait I frame, %s\n", FrameType(bIsField, m_PictureParams.bSecondField));
		return S_FALSE;
	}

	CHECK_HR_FALSE (GetFreeSurfaceIndex(nSurfaceIndex));

	if (!bIsField || (bIsField && !m_PictureParams.bSecondField)) {
		UpdatePictureParams(nSurfaceIndex);	
	}

	TRACE_MPEG2 ("CDXVA1DecoderMPEG2::DecodeFrame() : Surf = %d, %ws, m_nNextCodecIndex = %d, rtStart = [%I64d]\n",
				 nSurfaceIndex, FrameType(bIsField, m_PictureParams.bSecondField), m_nNextCodecIndex, rtStart);

	// Begin frame
	CHECK_HR_FALSE (BeginFrame(nSurfaceIndex));
	// Send picture parameters
	CHECK_HR_FRAME_DXVA1 (AddExecuteBuffer(DXVA_PICTURE_DECODE_BUFFER, sizeof(DXVA_PictureParameters), &m_PictureParams));
	// Send quantization matrix
	CHECK_HR_FRAME_DXVA1 (AddExecuteBuffer(DXVA_INVERSE_QUANTIZATION_MATRIX_BUFFER, sizeof(DXVA_QmatrixData), &m_QMatrixData));
	// Send bitstream
	CHECK_HR_FRAME_DXVA1 (AddExecuteBuffer(DXVA_BITSTREAM_DATA_BUFFER, nSize, pDataIn, &nSize));
	// Send slice control
	CHECK_HR_FRAME_DXVA1 (AddExecuteBuffer(DXVA_SLICE_CONTROL_BUFFER, sizeof(DXVA_SliceInfo) * m_nSliceCount, &m_SliceInfo));
	// Decode frame
	CHECK_HR_FRAME_DXVA1 (Execute());
	CHECK_HR_FALSE (EndFrame(nSurfaceIndex));

	bool bAdded = AddToStore(nSurfaceIndex, (m_PictureParams.bPicBackwardPrediction != 1),
							 rtStart, rtStop,
							 bIsField, FFGetCodedPicture(m_pFilter->GetAVCtx()));

	if (bAdded) {
		hr = DisplayNextFrame();
	}
		
	m_bFlushed = false;
	return hr;
}

void CDXVA1DecoderMPEG2::UpdatePictureParams(int nSurfaceIndex)
{
	DXVA_ConfigPictureDecode* cpd = &m_DXVA1Config;

	m_PictureParams.wDecodedPictureIndex = nSurfaceIndex;

	// Manage reference picture list
	if (!m_PictureParams.bPicBackwardPrediction) {
		if (m_wRefPictureIndex[0] != NO_REF_FRAME) {
			RemoveRefFrame (m_wRefPictureIndex[0]);
		}
		m_wRefPictureIndex[0] = m_wRefPictureIndex[1];
		m_wRefPictureIndex[1] = nSurfaceIndex;
	}
	m_PictureParams.wForwardRefPictureIndex		= (m_PictureParams.bPicIntra == 0)				? m_wRefPictureIndex[0] : NO_REF_FRAME;
	m_PictureParams.wBackwardRefPictureIndex	= (m_PictureParams.bPicBackwardPrediction == 1) ? m_wRefPictureIndex[1] : NO_REF_FRAME;

	// Shall be 0 if bConfigResidDiffHost is 0 or if BPP > 8
	if (cpd->bConfigResidDiffHost == 0 || m_PictureParams.bBPPminus1 > 7) {
		m_PictureParams.bPicSpatialResid8 = 0;
	} else {
		if (m_PictureParams.bBPPminus1 == 7 && m_PictureParams.bPicIntra && cpd->bConfigResidDiffHost) {
			// Shall be 1 if BPP is 8 and bPicIntra is 1 and bConfigResidDiffHost is 1
			m_PictureParams.bPicSpatialResid8 = 1;
		} else {
			// Shall be 1 if bConfigSpatialResid8 is 1
			m_PictureParams.bPicSpatialResid8 = cpd->bConfigSpatialResid8;
		}
	}

	// Shall be 0 if bConfigResidDiffHost is 0 or if bConfigSpatialResid8 is 0 or if BPP > 8
	if (cpd->bConfigResidDiffHost == 0 || cpd->bConfigSpatialResid8 == 0 || m_PictureParams.bBPPminus1 > 7) {
		m_PictureParams.bPicOverflowBlocks = 0;
	}

	// Shall be 1 if bConfigHostInverseScan is 1 or if bConfigResidDiffAccelerator is 0.

	if (cpd->bConfigHostInverseScan == 1 || cpd->bConfigResidDiffAccelerator == 0) {
		m_PictureParams.bPicScanFixed	= 1;

		if (cpd->bConfigHostInverseScan != 0) {
			m_PictureParams.bPicScanMethod	= 3;    // 11 = Arbitrary scan with absolute coefficient address.
		} else if (FFGetAlternateScan(m_pFilter->GetAVCtx())) {
			m_PictureParams.bPicScanMethod	= 1;    // 00 = Zig-zag scan (MPEG-2 Figure 7-2)
		} else {
			m_PictureParams.bPicScanMethod	= 0;    // 01 = Alternate-vertical (MPEG-2 Figure 7-3),
		}
	}
}

void CDXVA1DecoderMPEG2::CopyBitstream(BYTE* pDXVABuffer, BYTE* pBuffer, UINT& nSize)
{
	while (*((DWORD*)pBuffer) != 0x01010000) {
		pBuffer++;
		nSize--;

		if (nSize == 0) {
			return;
		}
	}

	memcpy(pDXVABuffer, pBuffer, nSize);
}

void CDXVA1DecoderMPEG2::Flush()
{
	m_nNextCodecIndex		= INT_MIN;

	m_wRefPictureIndex[0]	= NO_REF_FRAME;
	m_wRefPictureIndex[1]	= NO_REF_FRAME;

	__super::Flush();
}

int CDXVA1DecoderMPEG2::FindOldestFrame()
{
	int nPos = -1;

	for (int i = 0; i < m_nPicEntryNumber; i++) {
		if (!m_pPictureStore[i].bDisplayed && m_pPictureStore[i].bInUse &&
				(m_pPictureStore[i].nCodecSpecific == m_nNextCodecIndex)) {
			m_nNextCodecIndex	= INT_MIN;
			nPos				= i;
		}
	}

	if (nPos != -1) {
		m_pFilter->UpdateFrameTime(m_pPictureStore[nPos].rtStart, m_pPictureStore[nPos].rtStop);
	}

	return nPos;
}
