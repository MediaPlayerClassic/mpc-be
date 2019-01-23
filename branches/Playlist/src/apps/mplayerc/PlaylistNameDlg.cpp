/*
 * (C) 2003-2006 Gabest
 * (C) 2006-2018 see Authors.txt
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
#include "PlaylistNameDlg.h"

 // CAddPlaylistDlg dialog

IMPLEMENT_DYNAMIC(CPlaylistNameDlg, CCmdUIDialog)
CPlaylistNameDlg::CPlaylistNameDlg(CString& str, CWnd* pParent/* = nullptr*/)
	: CCmdUIDialog(CPlaylistNameDlg::IDD, pParent)
	, m_name(str)
{
}

CPlaylistNameDlg::~CPlaylistNameDlg()
{
}

void CPlaylistNameDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PLAYLISTNAME, m_name);
	DDX_Control(pDX, IDC_EDIT_PLAYLISTNAME, m_namectrl);
}

BOOL CPlaylistNameDlg::OnInitDialog()
{
	__super::OnInitDialog();


	UpdateData(FALSE);
	
	GetDlgItem(IDC_EDIT_PLAYLISTNAME)->SetFocus();
	//m_name = L"Playlist #";
	m_namectrl.SetWindowText(m_name);
	m_namectrl.SetSel(0, -1);

	return FALSE;
}

BEGIN_MESSAGE_MAP(CPlaylistNameDlg, CCmdUIDialog)
	ON_UPDATE_COMMAND_UI(IDOK, OnUpdateOk)
END_MESSAGE_MAP()

// CAddPlaylistDlg message handlers

void CPlaylistNameDlg::OnUpdateOk(CCmdUI *pCmdUI)
{
	UpdateData();

	pCmdUI->Enable(!m_name.IsEmpty());
}

void CPlaylistNameDlg::OnOK()
{
	UpdateData();

	CCmdUIDialog::OnOK();
}
