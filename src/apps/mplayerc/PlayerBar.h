/*
 * (C) 2014-2021 see Authors.txt
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


#pragma once

#include <ExtLib/ui/sizecbar/scbarg.h>

class CPlayerBar : public CSizingControlBarG
{
	DECLARE_DYNAMIC(CPlayerBar)

protected :
	DECLARE_MESSAGE_MAP()

	UINT m_defDockBarID;
	CString m_strSettingName;

public:
	CPlayerBar();
	virtual ~CPlayerBar();

	BOOL Create(LPCWSTR lpszWindowName, CWnd* pParentWnd, UINT nID, UINT defDockBarID, CString const& strSettingName);

	virtual void ReloadTranslatableResources() PURE;

	virtual void LoadState(CFrameWnd *pParent);
	virtual void SaveState();

	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz) override;
};
