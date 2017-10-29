/*
 * (C) 2017 see Authors.txt
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
#include <MMReg.h>
#include "SampleFormat.h"
#include "AudioDecoders.h"

void bswap16_buf(uint16_t* dst16, const uint16_t* src16, unsigned len)
{
	while (len--) {
		*dst16++ = _byteswap_ushort(*src16++);
	}
}

void dvdlpcm20_to_pcm32(uint32_t* dst32, const uint8_t* src, unsigned blocks, const unsigned channels)
{
	while (blocks--) {
		const uint8_t* b = src + channels * 4;
		for (unsigned i = 0; i < channels; ++i) {
			*dst32++ = (src[0] << 24) | (src[1] << 16) | ((*b & 0xF0) << 8);
			*dst32++ = (src[2] << 24) | (src[3] << 16) | ((*b & 0x0F) << 12);
			src += 4;
			b++;
		}
		src = b;
	}
}

void dvdlpcm24_to_pcm32(uint32_t* dst32, const uint8_t* src, unsigned blocks, const unsigned channels)
{
	while (blocks--) {
		const uint8_t* b = src + channels * 4;
		for (unsigned i = 0; i < channels; ++i) {
			*dst32++ = (src[0] << 24) | (src[1] << 16) | (*b++ << 8);
			*dst32++ = (src[2] << 24) | (src[3] << 16) | (*b++ << 8);
			src += 4;
		}
		src = b;
	}
}

std::unique_ptr<BYTE[]> DecodeDvdLPCM(unsigned& dst_size, SampleFormat& dst_sf, BYTE* src, unsigned& src_size, const unsigned channels, const unsigned bitdepth)
{
	// https://wiki.multimedia.cx/index.php/PCM#DVD_PCM

	const unsigned blocksize = channels * 2 * bitdepth / 8;
	if (!blocksize || blocksize > src_size) {
		return nullptr;
	}

	const unsigned blocks = src_size / blocksize;
	const unsigned allsamples = blocks * 2 * channels;

	dst_size = allsamples * (bitdepth <= 16 ? 2 : 4); // convert to 16 and 32-bit
	std::unique_ptr<BYTE[]> dst(new(std::nothrow) BYTE[dst_size]);
	if (!dst) {
		return nullptr;
	}

	if (bitdepth == 16) {
		bswap16_buf((uint16_t*)dst.get(), (uint16_t*)src, allsamples);
		dst_sf = SAMPLE_FMT_S16;
	}
	else if (bitdepth == 20) {
		dvdlpcm20_to_pcm32((uint32_t*)dst.get(), src, blocks, channels);
		dst_sf = SAMPLE_FMT_S32;
	}
	else if (bitdepth == 24) {
		dvdlpcm24_to_pcm32((uint32_t*)dst.get(), src, blocks, channels);
		dst_sf = SAMPLE_FMT_S32;
	}

	src_size %= blocksize;

	return dst;
}

std::unique_ptr<BYTE[]> DecodeHdmvLPCM(unsigned& dst_size, SampleFormat& dst_sf, BYTE* src, unsigned& src_size, const unsigned channels, const unsigned bitdepth, const BYTE channel_conf)
{
	const unsigned framesize = ((channels + 1) & ~1) * ((bitdepth + 7) / 8);
	if (!framesize) {
		return nullptr;
	}
	const unsigned frames = src_size / framesize;

	dst_size = frames * channels * (bitdepth <= 16 ? 2 : 4); // convert to 16 and 32-bit
	std::unique_ptr<BYTE[]> dst(new(std::nothrow) BYTE[dst_size]);
	if (!dst) {
		return nullptr;
	}

	auto& remap = s_scmap_hdmv[channel_conf].ch;

	if (bitdepth == 16) {
		uint16_t* src16 = (uint16_t*)src;
		uint16_t* dst16 = (uint16_t*)dst.get();

		for (unsigned i = 0; i < frames; ++i) {
			for (unsigned j = 0; j < channels; ++j) {
				*(dst16++) = _byteswap_ushort(src16[remap[j]]);
			}
			src += framesize;
		}
		dst_sf = SAMPLE_FMT_S16;
	}
	else if (bitdepth == 20 || bitdepth == 24) {
		uint32_t* dst32 = (uint32_t*)dst.get(); // convert to 32-bit

		for (unsigned i = 0; i < frames; i++) {
			for (unsigned j = 0; j < channels; j++) {
				unsigned n = remap[j] * 3;
				*(dst32++) = (src[n] << 24) | (src[n + 1] << 16) | (src[n + 2] << 8);
			}
			src += framesize;
		}
		dst_sf = SAMPLE_FMT_S32;
	}

	src_size %= framesize;

	return dst;
}

std::unique_ptr<BYTE[]> DecodeDvdaLPCM(unsigned& dst_size, SampleFormat& dst_sf, BYTE* src, unsigned& src_size, const DVDA_INFO& a)
{
	const unsigned blocksize1 = 2 * a.channels1 * a.bitdepth1 / 8;
	const unsigned blocksize2 = 2 * a.channels2 * a.bitdepth2 / 8;
	const unsigned blocksize = blocksize1 + blocksize2;

	if (blocksize > src_size) {
		return nullptr;
	}

	const unsigned blocks = src_size / blocksize;
	const unsigned allsamples1 = blocks * 2 * a.channels1;

	dst_size = allsamples1 * (a.bitdepth1 <= 16 ? 2 : 4); // convert to 16 and 32-bit
	std::unique_ptr<BYTE[]> dst(new(std::nothrow) BYTE[dst_size]);
	if (!dst) {
		return nullptr;
	}

	uint16_t* dst16 = (uint16_t*)dst.get();
	uint32_t* dst32 = (uint32_t*)dst.get();

	for (unsigned n = 0; n < blocks; ++n) {
		src += blocksize2;

		if (a.bitdepth1 == 16) {
			uint16_t* src16 = (uint16_t*)src;

			for (unsigned i = 0; i < allsamples1; ++i) {
				*(dst16++) = _byteswap_ushort(*src16++);
			}
			dst_sf = SAMPLE_FMT_S16;
			src = (BYTE*)src16;
		}
		else if (a.bitdepth1 == 20) {
			if (a.channels1 == 1) {
				for (unsigned i = 0; i < allsamples1; i += 2) {
					*(dst32++) = (src[0] << 24) | (src[1] << 16) | ((src[4] & 0xF0) << 8);
					*(dst32++) = (src[2] << 24) | (src[3] << 16) | ((src[4] & 0x0F) << 12);
					src += 5;
				}
			}
			else {
				for (unsigned i = 0; i < allsamples1; i += 4) {
					*(dst32++) = (src[0] << 24) | (src[1] << 16) | ((src[8] & 0xF0) << 8);
					*(dst32++) = (src[2] << 24) | (src[3] << 16) | ((src[8] & 0x0F) << 12);
					*(dst32++) = (src[4] << 24) | (src[5] << 16) | ((src[9] & 0xF0) << 8);
					*(dst32++) = (src[6] << 24) | (src[7] << 16) | ((src[9] & 0x0F) << 12);
					src += 10;
				}
			}
			dst_sf = SAMPLE_FMT_S32;
		}
		else if (a.bitdepth1 == 24) {
			if (a.channels1 == 1) {
				for (unsigned i = 0; i < 2 * a.channels1; i += 2) {
					*(dst32++) = (src[0] << 24) | (src[1] << 16) | (src[4] << 8);
					*(dst32++) = (src[2] << 24) | (src[3] << 16) | (src[5] << 8);
					src += 6;
				}
			}
			else {
				for (unsigned i = 0; i < 2 * a.channels1; i += 4) {
					*(dst32++) = (src[0] << 24) | (src[1] << 16) | (src[8] << 8);
					*(dst32++) = (src[2] << 24) | (src[3] << 16) | (src[9] << 8);
					*(dst32++) = (src[4] << 24) | (src[5] << 16) | (src[10] << 8);
					*(dst32++) = (src[6] << 24) | (src[7] << 16) | (src[11] << 8);
					src += 12;
				}
			}
			dst_sf = SAMPLE_FMT_S32;
		}
	}

	src_size %= blocksize;

	return dst;
}
