/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2016 see Authors.txt
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
#include <io.h>
#include <regex>
#include "TextFile.h"
#include "SubtitleHelpers.h"

static LPCTSTR separators = _T(".\\-_");
static LPCTSTR extListVid = _T("(avi)|(mkv)|(mp4)|((m2)?ts)");

LPCTSTR Subtitle::GetSubtitleFileExt(SubType type)
{
	return (type >= 0 && size_t(type) < subTypesExt.size()) ? subTypesExt[type] : nullptr;
}

static int SubFileCompare(const void* elem1, const void* elem2)
{
	return ((Subtitle::SubFile*)elem1)->fn.CompareNoCase(((Subtitle::SubFile*)elem2)->fn);
}

void Subtitle::GetSubFileNames(CString fn, const CAtlArray<CString>& paths, CAtlArray<SubFile>& ret)
{
	ret.RemoveAll();

	fn.Replace('\\', '/');

	bool fWeb = false;
	{
		//int i = fn.Find(_T("://"));
		int i = fn.Find(_T("http://"));
		if (i > 0) {
			fn = _T("http") + fn.Mid(i);
			fWeb = true;
		}
	}

	int l  = fn.ReverseFind('/') + 1;
	int l2 = fn.ReverseFind('.');
	if (l2 < l) { // no extension, read to the end
		l2 = fn.GetLength();
	}

	CString orgpath = fn.Left(l);
	CString title = fn.Mid(l, l2 - l);
	int titleLength = title.GetLength();
	//CString filename = title + _T(".nooneexpectsthespanishinquisition");

	if (!fWeb) {
		WIN32_FIND_DATA wfd;

		CString extListSub, regExpSub, regExpVid;
		for (size_t i = 0; i < subTypesExt.size(); i++) {
			extListSub.AppendFormat(_T("(%s)"), subTypesExt[i]);
			if (i < subTypesExt.size() - 1) {
				extListSub.AppendChar(_T('|'));
			}
		}
		regExpSub.Format(_T("([%s]+.+)?\\.(%s)$"), separators, extListSub);
		regExpVid.Format(_T(".+\\.(%s)$"), extListVid);

		const std::wregex::flag_type reFlags = std::wregex::icase | std::wregex::optimize;
		std::wregex reSub(regExpSub, reFlags), reVid(regExpVid, reFlags);

		for (size_t k = 0; k < paths.GetCount(); k++) {
			CString path = paths[k];
			path.Replace(L'\\', L'/');

			l = path.GetLength();
			if (l > 0 && path[l - 1] != L'/') {
				path += L'/';
			}

			if (path.Find(':') == -1 && path.Find(_T("//")) != 0) {
				path = orgpath + path;
			}

			path.Replace(_T("/./"), _T("/"));
			path.Replace(L'/', L'\\');

			CAtlList<CString> subs, vids;

			HANDLE hFile = FindFirstFile(path + title + _T("*"), &wfd);
			if (hFile != INVALID_HANDLE_VALUE) {
				do {
					CString fn = path + wfd.cFileName;
					if (std::regex_match(&wfd.cFileName[titleLength], reSub)) {
						subs.AddTail(fn);
					} else if (std::regex_match(&wfd.cFileName[titleLength], reVid)) {
						// Convert to lower-case and cut the extension for easier matching
						vids.AddTail(fn.Left(fn.ReverseFind(_T('.'))).MakeLower());
					}
				} while (FindNextFile(hFile, &wfd));

				FindClose(hFile);
			}

			POSITION posSub = subs.GetHeadPosition();
			while (posSub) {
				CString& fn = subs.GetNext(posSub);
				CString fnlower = fn;
				fnlower.MakeLower();

				// Check if there is an exact match for another video file
				bool bMatchAnotherVid = false;
				POSITION posVid = vids.GetHeadPosition();
				while (posVid) {
					if (fnlower.Find(vids.GetNext(posVid)) == 0) {
						bMatchAnotherVid = true;
						break;
					}
				}

				if (!bMatchAnotherVid) {
					SubFile f;
					f.fn = fn;
					ret.Add(f);
				}
			}
		}
	} else if (l > 7) {
		CWebTextFile wtf; // :)
		if (wtf.Open(orgpath + title + _T(".wse"))) {
			CString fn2;
			while (wtf.ReadString(fn2) && fn2.Find(_T("://")) >= 0) {
				SubFile f;
				f.fn = fn2;
				ret.Add(f);
			}
		}
	}

	// sort files, this way the user can define the order (movie.00.English.srt, movie.01.Hungarian.srt, etc)

	qsort(ret.GetData(), ret.GetCount(), sizeof(SubFile), SubFileCompare);
}

CString Subtitle::GuessSubtitleName(CString fn, CString videoName)
{
	CString name, lang;
	bool bHearingImpaired = false;

	// The filename of the subtitle file
	int iExtStart = fn.ReverseFind('.');
	if (iExtStart < 0) {
		iExtStart = fn.GetLength();
	}
	CString subName = fn.Left(iExtStart).Mid(fn.ReverseFind('\\') + 1);

	if (!videoName.IsEmpty()) {
		// The filename of the video file
		iExtStart = videoName.ReverseFind('.');
		if (iExtStart < 0) {
			iExtStart = videoName.GetLength();
		}
		CString videoExt = videoName.Mid(iExtStart + 1).MakeLower();
		videoName = videoName.Left(iExtStart).Mid(videoName.ReverseFind('\\') + 1);

		CString subNameNoCase = CString(subName).MakeLower();
		CString videoNameNoCase = CString(videoName).MakeLower();

		// Check if the subtitle filename starts with the video filename
		// so that we can try to find a language info right after it
		if (subNameNoCase.Find(videoNameNoCase) == 0) {
			int iVideoNameEnd = videoName.GetLength();
			// Get ride of the video extension if it's in the subtitle filename
			if (subNameNoCase.Find(videoExt, iVideoNameEnd) == iVideoNameEnd + 1) {
				iVideoNameEnd += 1 + videoExt.GetLength();
			}
			subName = subName.Mid(iVideoNameEnd);

			std::wregex re(_T("^[.\\-_ ]+([^.\\-_ ]+)(?:[.\\-_ ]+([^.\\-_ ]+))?"), std::wregex::icase);
			std::wcmatch mc;
			if (std::regex_search((LPCTSTR)subName, mc, re)) {
				ASSERT(mc.size() == 3);
				ASSERT(mc[1].matched);
				lang = ISO639XToLanguage(CStringA(mc[1].str().c_str()), true);

				if (!lang.IsEmpty() && mc[2].matched) {
					bHearingImpaired = (CString(mc[2].str().c_str()).CompareNoCase(_T("hi")) == 0);
				}
			}
		}
	}

	// If we couldn't find any info yet, we try to find the language at the end of the filename
	if (lang.IsEmpty()) {
		std::wregex re(_T(".*?[.\\-_ ]+([^.\\-_ ]+)(?:[.\\-_ ]+([^.\\-_ ]+))?$"), std::wregex::icase);
		std::wcmatch mc;
		if (std::regex_search((LPCTSTR)subName, mc, re)) {
			ASSERT(mc.size() == 3);
			ASSERT(mc[1].matched);
			lang = ISO639XToLanguage(CStringA(mc[1].str().c_str()), true);

			CStringA str;
			if (mc[2].matched) {
				str = mc[2].str().c_str();
			}

			if (!lang.IsEmpty() && str.CompareNoCase("hi") == 0) {
				bHearingImpaired = true;
			} else {
				lang = ISO639XToLanguage(str, true);
			}
		}
	}

	name = fn.Mid(fn.ReverseFind('\\') + 1);
	if (name.GetLength() > 100) { // Cut some part of the filename if it's too long
		name.Format(_T("%s...%s"), name.Left(50).TrimRight(_T(".-_ ")), name.Right(50).TrimLeft(_T(".-_ ")));
	}
	if (!lang.IsEmpty()) {
		name.AppendFormat(_T(" [%s]"), lang);
		if (bHearingImpaired) {
			name.Append(_T(" [hearing impaired]"));
		}
	}

	return name;
}
