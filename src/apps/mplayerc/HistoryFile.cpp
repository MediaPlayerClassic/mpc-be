/*
 * (C) 2021 see Authors.txt
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
#include "HistoryFile.h"
#include <atlenc.h>

//
// CMpcLstFile
//

bool CMpcLstFile::ReadFile()
{
	if (!::PathFileExistsW(m_filename)) {
		return false;
	}

	const DWORD tick = GetTickCount();
	if (m_LastAccessTick && std::labs(tick - m_LastAccessTick) < 100) {
		return true;
	}

	FILE* fp;
	int fpStatus;
	do { // Open mpc-be.ini in UNICODE mode, retry if it is already being used by another process
		fp = _wfsopen(m_filename, L"r, ccs=UNICODE", _SH_SECURE);
		if (fp || (GetLastError() != ERROR_SHARING_VIOLATION)) {
			break;
		}
		Sleep(100);
	} while (true);
	if (!fp) {
		ASSERT(0);
		return false;;
	}

	CStdioFile file(fp);

	IntClearEntries();

	SessionInfo sesInfo;
	CStringW section;
	CStringW line;

	while (file.ReadString(line)) {
		int pos = 0;

		if (line[0] == '[') { // new section
			if (section.GetLength()) {
				section.Empty();
				IntAddEntry(sesInfo);
				sesInfo = {};
			}

			pos = line.Find(']');
			if (pos > 0) {
				section = line.Mid(1, pos - 1);
			}
			continue;
		}

		if (line[0] == ';' || section.IsEmpty()) {
			continue;
		}

		pos = line.Find('=');
		if (pos > 0 && pos + 1 < line.GetLength()) {
			CStringW param = line.Mid(0, pos).Trim();
			CStringW value = line.Mid(pos + 1).Trim();
			if (value.GetLength()) {
				if (param == L"Path") {
					sesInfo.Path = value;
				}
				else if (param == L"Position") {
					int h, m, s;
					if (swscanf_s(value, L"%02d:%02d:%02d", &h, &m, &s) == 3) {
						sesInfo.Position = (((h * 60) + m) * 60 + s) * UNITS;
					}
				}
				else if (param == L"DVDId") {
					StrHexToUInt64(value, sesInfo.DVDId);
				}
				else if (param == L"DVDPosition") {
					unsigned dvdTitle, h, m, s;
					if (swscanf_s(value, L"%02u,%02u:%02u:%02u", &dvdTitle, &h, &m, &s) == 4) {
						sesInfo.DVDTitle = dvdTitle;
						sesInfo.DVDTimecode = { (BYTE)h, (BYTE)m, (BYTE)s, 0 };
					}
				}
				else if (param == L"DVDState") {
					CStringA base64(value);
					int nDestLen = Base64DecodeGetRequiredLength(base64.GetLength());
					sesInfo.DVDState.resize(nDestLen);
					BOOL ret = Base64Decode(base64, base64.GetLength(), sesInfo.DVDState.data(), &nDestLen);
					if (ret) {
						sesInfo.DVDState.resize(nDestLen);
					} else {
						sesInfo.DVDState.clear();
					}
				}
				else if (param == L"AudioNum") {
					int32_t i32val;
					if (StrToInt32(value, i32val) && i32val >= 1) {
						sesInfo.AudioNum = i32val - 1;
					}
				}
				else if (param == L"SubtitleNum") {
					int32_t i32val;
					if (StrToInt32(value, i32val) && i32val >= 1) {
						sesInfo.SubtitleNum = i32val - 1;
					}
				}
				else if (param == L"AudioPath") {
					sesInfo.AudioPath = value;
				}
				else if (param == L"SubtitlePath") {
					sesInfo.SubtitlePath = value;
				}
				else if (param == L"Title") {
					sesInfo.Title = value;
				}
			}
		}
	}

	fpStatus = fclose(fp);
	ASSERT(fpStatus == 0);
	m_LastAccessTick = GetTickCount();

	if (section.GetLength()) {
		IntAddEntry(sesInfo);
	}

	return true;
}

bool CMpcLstFile::Clear()
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	if (_wremove(m_filename) == 0 || errno == ENOENT) {
		IntClearEntries();
		return true;
	}
	return false;
}

void CMpcLstFile::SetFilename(const CStringW& filename)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	m_filename = filename;
}

void CMpcLstFile::SetMaxCount(unsigned maxcount)
{
	m_maxCount = std::clamp(maxcount, 10u, 999u);
}

//
// CHistoryFile
//

void CHistoryFile::IntAddEntry(const SessionInfo& sesInfo)
{
	if (sesInfo.Path.GetLength()) {
		m_SessionInfos.emplace_back(sesInfo);
	}
}

void CHistoryFile::IntClearEntries()
{
	m_SessionInfos.clear();
}

std::list<SessionInfo>::iterator CHistoryFile::FindSessionInfo(const SessionInfo& sesInfo, std::list<SessionInfo>::iterator begin)
{
	if (sesInfo.DVDId) {
		for (auto it = begin; it != m_SessionInfos.end(); ++it) {
			if (sesInfo.DVDId == (*it).DVDId) {
				return it;
			}
		}
	}
	else if (sesInfo.Path.GetLength()) {
		for (auto it = begin; it != m_SessionInfos.end(); ++it) {
			if (sesInfo.Path.CompareNoCase((*it).Path) == 0) {
				return it;
			}
		}
	}
	else {
		ASSERT(0);
	}

	return m_SessionInfos.end();
}

bool CHistoryFile::WriteFile()
{
	FILE* fp;
	int fpStatus;
	do { // Open file, retry if it is already being used by another process
		fp = _wfsopen(m_filename, L"w, ccs=UTF-8", _SH_SECURE);
		if (fp || (GetLastError() != ERROR_SHARING_VIOLATION)) {
			break;
		}
		Sleep(100);
	} while (true);
	if (!fp) {
		ASSERT(FALSE);
		return false;
	}

	bool ret = true;

	CStdioFile file(fp);
	CStringW str;
	try {
		file.WriteString(L"; MPC-BE History File 0.1\n");
		int i = 1;
		for (const auto& sesInfo : m_SessionInfos) {
			if (sesInfo.Path.GetLength()) {
				str.Format(L"\n[%03d]\n", i++);

				str.AppendFormat(L"Path=%s\n", sesInfo.Path);

				if (sesInfo.Title.GetLength()) {
					str.AppendFormat(L"Title=%s\n", sesInfo.Title);
				}

				if (sesInfo.DVDId) {
					str.AppendFormat(L"DVDId=%016I64x\n", sesInfo.DVDId);
					if (sesInfo.DVDTitle) {
						str.AppendFormat(L"DVDPosition=%02u,%02u:%02u:%02u\n",
							(unsigned)sesInfo.DVDTitle,
							(unsigned)sesInfo.DVDTimecode.bHours,
							(unsigned)sesInfo.DVDTimecode.bMinutes,
							(unsigned)sesInfo.DVDTimecode.bSeconds);
					}
					if (sesInfo.DVDState.size()) {
						int nDestLen = Base64EncodeGetRequiredLength(sesInfo.DVDState.size());
						CStringA base64;
						BOOL ret = Base64Encode(sesInfo.DVDState.data(), sesInfo.DVDState.size(), base64.GetBuffer(nDestLen), &nDestLen, ATL_BASE64_FLAG_NOCRLF);
						if (ret) {
							base64.ReleaseBufferSetLength(nDestLen);
							str.AppendFormat(L"DVDState=%hs\n", base64);
						}
					}
				}
				else {
					if (sesInfo.Position > UNITS) {
						LONGLONG seconds = sesInfo.Position / UNITS;
						int h = (int)(seconds / 3600);
						int m = (int)(seconds / 60 % 60);
						int s = (int)(seconds % 60);
						str.AppendFormat(L"Position=%02d:%02d:%02d\n", h, m, s);
					}
					if (sesInfo.AudioNum >= 0) {
						str.AppendFormat(L"AudioNum=%d\n", sesInfo.AudioNum + 1);
					}
					if (sesInfo.SubtitleNum >= 0) {
						str.AppendFormat(L"SubtitleNum=%d\n", sesInfo.SubtitleNum + 1);
					}
					if (sesInfo.AudioPath.GetLength()) {
						str.AppendFormat(L"AudioPath=%s\n", sesInfo.AudioPath);
					}
					if (sesInfo.SubtitlePath.GetLength()) {
						str.AppendFormat(L"SubtitlePath=%d\n", sesInfo.SubtitlePath);
					}
				}
				file.WriteString(str);
			}
		}
	}
	catch (CFileException& e) {
		// Fail silently if disk is full
		UNREFERENCED_PARAMETER(e);
		ASSERT(FALSE);
		ret = false;
	}

	fpStatus = fclose(fp);
	ASSERT(fpStatus == 0);
	m_LastAccessTick = GetTickCount();

	return ret;
}

bool CHistoryFile::OpenSessionInfo(SessionInfo& sesInfo, bool bReadPos)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	ReadFile();

	bool found = false;
	auto it = FindSessionInfo(sesInfo, m_SessionInfos.begin());

	if (it != m_SessionInfos.end()) {
		found = true;
		auto& si = (*it);

		if (bReadPos) {
			if (sesInfo.DVDId) {
				sesInfo.DVDTitle    = si.DVDTitle;
				sesInfo.DVDTimecode = si.DVDTimecode;
				sesInfo.DVDState    = si.DVDState;
			}
			else if (sesInfo.Path.GetLength()) {
				sesInfo.Position     = si.Position;
				sesInfo.AudioNum     = si.AudioNum;
				sesInfo.SubtitleNum  = si.SubtitleNum;
				sesInfo.AudioPath    = si.AudioPath;
				sesInfo.SubtitlePath = si.SubtitlePath;
			}
		}

		if (sesInfo.Title.IsEmpty()) {
			sesInfo.Title = si.Title;
		}
	}

	if (it != m_SessionInfos.begin() || !found) { // not first entry or empty list
		if (found) {
			m_SessionInfos.erase(it);
		}

		m_SessionInfos.emplace_front(sesInfo);

		while (m_SessionInfos.size() > m_maxCount) {
			m_SessionInfos.pop_back();
		}
		WriteFile();
	}

	return found;
}

void CHistoryFile::SaveSessionInfo(const SessionInfo& sesInfo)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	ReadFile();

	auto it = FindSessionInfo(sesInfo, m_SessionInfos.begin());

	if (it == m_SessionInfos.begin() && sesInfo.Equals(*it)) {
		return;
	}

	if (it != m_SessionInfos.end()) {
		m_SessionInfos.erase(it);
	}

	m_SessionInfos.emplace_front(sesInfo); // Writing new data

	while (m_SessionInfos.size() > m_maxCount) {
		m_SessionInfos.pop_back();
	}

	WriteFile();
}

bool CHistoryFile::DeleteSessions(const std::list<SessionInfo>& sessions)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	if (!ReadFile()) {
		return false;
	}

	bool changed = false;

	for (const auto& sesInfo : sessions) {
		auto it = FindSessionInfo(sesInfo, m_SessionInfos.begin());

		// delete what was found and all unexpected duplicates (for example, after manual editing)
		while (it != m_SessionInfos.end()) {
			m_SessionInfos.erase(it++);
			changed = true;
			it = FindSessionInfo(sesInfo, it);
		}
	}

	if (changed) {
		return WriteFile();
	}

	return true; // already deleted
}

void CHistoryFile::GetRecentPaths(std::vector<CStringW>& recentPaths, unsigned count)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	recentPaths.clear();
	ReadFile();

	if (count > m_SessionInfos.size()) {
		count = m_SessionInfos.size();
	}

	if (count) {
		recentPaths.reserve(count);
		auto it = m_SessionInfos.cbegin();
		for (unsigned i = 0; i < count; i++) {
			recentPaths.emplace_back((*it++).Path);
		}
	}
}

void CHistoryFile::GetRecentSessions(std::vector<SessionInfo>& recentSessions, unsigned count)
{
	std::lock_guard<std::mutex> lock(m_Mutex);

	recentSessions.clear();
	ReadFile();

	if (count > m_SessionInfos.size()) {
		count = m_SessionInfos.size();
	}

	if (count) {
		recentSessions.reserve(count);
		auto it = m_SessionInfos.cbegin();
		for (unsigned i = 0; i < count; i++) {
			recentSessions.emplace_back(*it++);
		}
	}
}

//
// CFavoritesFile
//

void CFavoritesFile::IntAddEntry(const SessionInfo& sesInfo)
{
	if (sesInfo.Path.GetLength()) {
		if (sesInfo.DVDId) {
			m_FavDVDs.emplace_back(sesInfo);
		} else {
			m_FavFiles.emplace_back(sesInfo);
		}
	}
}

void CFavoritesFile::IntClearEntries()
{
	m_FavFiles.clear();
	m_FavDVDs.clear();
}

bool CFavoritesFile::WriteFile()
{
	FILE* fp;
	int fpStatus;
	do { // Open file, retry if it is already being used by another process
		fp = _wfsopen(m_filename, L"w, ccs=UTF-8", _SH_SECURE);
		if (fp || (GetLastError() != ERROR_SHARING_VIOLATION)) {
			break;
		}
		Sleep(100);
	} while (true);
	if (!fp) {
		ASSERT(FALSE);
		return false;
	}

	bool ret = true;

	CStdioFile file(fp);
	CStringW str;
	try {
		file.WriteString(L"; MPC-BE Favorites File 0.1\n");
		int i = 1;
		for (const auto& sesInfo : m_FavFiles) {
			if (sesInfo.Path.GetLength()) {
				str.Format(L"\n[%03d]\n", i++);

				str.AppendFormat(L"Path=%s\n", sesInfo.Path);

				if (sesInfo.Title.GetLength()) {
					str.AppendFormat(L"Title=%s\n", sesInfo.Title);
				}
				if (sesInfo.Position > UNITS) {
					LONGLONG seconds = sesInfo.Position / UNITS;
					int h = (int)(seconds / 3600);
					int m = (int)(seconds / 60 % 60);
					int s = (int)(seconds % 60);
					str.AppendFormat(L"Position=%02d:%02d:%02d\n", h, m, s);
				}
				if (sesInfo.AudioNum >= 0) {
					str.AppendFormat(L"AudioNum=%d\n", sesInfo.AudioNum + 1);
				}
				if (sesInfo.SubtitleNum >= 0) {
					str.AppendFormat(L"SubtitleNum=%d\n", sesInfo.SubtitleNum + 1);
				}
				if (sesInfo.AudioPath.GetLength()) {
					str.AppendFormat(L"AudioPath=%s\n", sesInfo.AudioPath);
				}
				if (sesInfo.SubtitlePath.GetLength()) {
					str.AppendFormat(L"SubtitlePath=%d\n", sesInfo.SubtitlePath);
				}

				file.WriteString(str);
			}
		}

		for (const auto& sesDvd : m_FavDVDs) {
			if (sesDvd.Path.GetLength() && sesDvd.DVDId) {
				str.Format(L"\n[%03d]\n", i++);

				str.AppendFormat(L"Path=%s\n", sesDvd.Path);

				if (sesDvd.Title.GetLength()) {
					str.AppendFormat(L"Title=%s\n", sesDvd.Title);
				}

				str.AppendFormat(L"DVDId=%016I64x\n", sesDvd.DVDId);

				if (sesDvd.DVDTitle) {
					str.AppendFormat(L"DVDPosition=%02u,%02u:%02u:%02u\n",
						(unsigned)sesDvd.DVDTitle,
						(unsigned)sesDvd.DVDTimecode.bHours,
						(unsigned)sesDvd.DVDTimecode.bMinutes,
						(unsigned)sesDvd.DVDTimecode.bSeconds);
				}
				if (sesDvd.DVDState.size()) {
					int nDestLen = Base64EncodeGetRequiredLength(sesDvd.DVDState.size());
					CStringA base64;
					BOOL ret = Base64Encode(sesDvd.DVDState.data(), sesDvd.DVDState.size(), base64.GetBuffer(nDestLen), &nDestLen, ATL_BASE64_FLAG_NOCRLF);
					if (ret) {
						base64.ReleaseBufferSetLength(nDestLen);
						str.AppendFormat(L"DVDState=%hs\n", base64);
					}
				}

				file.WriteString(str);
			}
		}
	}
	catch (CFileException& e) {
		// Fail silently if disk is full
		UNREFERENCED_PARAMETER(e);
		ASSERT(FALSE);
		ret = false;
	}

	fpStatus = fclose(fp);
	ASSERT(fpStatus == 0);
	m_LastAccessTick = GetTickCount();

	return ret;
}

void CFavoritesFile::OpenFavorites()
{
	IntClearEntries();
	ReadFile();
}

void CFavoritesFile::SaveFavorites()
{
	WriteFile();
}
