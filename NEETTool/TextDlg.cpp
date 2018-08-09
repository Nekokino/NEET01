// TextDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NEETTool.h"
#include "TextDlg.h"
#include "afxdialogex.h"

#include "NTDlgShortCut.h"
#include <NTFontRenderer.h>
#include <NTReadStream.h>
#include <NTWriteStream.h>
#include <GameSystem.h>
#include <ResourceSystem.h>


// TextDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(TextDlg, CDialogEx)

TextDlg::TextDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_TEXTDLG, pParent)
	, UserText(_T(""))
	, CurText(_T(""))
	, CurIndex(_T(""))
	, UserIndex(_T(""))
{
	NTDlgShortCut::pTextDlg = this;
}

TextDlg::~TextDlg()
{
}

void TextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_USERTEXT, UserText);
	DDX_Text(pDX, IDC_CURTEXT, CurText);
	DDX_Text(pDX, IDC_CURINDEX, CurIndex);
	DDX_Text(pDX, IDC_USERINDEX, UserIndex);
}


BEGIN_MESSAGE_MAP(TextDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &TextDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &TextDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_USERINDEX, &TextDlg::OnEnChangeUserindex)
	ON_BN_CLICKED(IDC_SAVETEXT, &TextDlg::OnBnClickedSavetext)
	ON_BN_CLICKED(IDC_LOADTEXT, &TextDlg::OnBnClickedLoadtext)
	ON_EN_CHANGE(IDC_USERTEXT, &TextDlg::OnEnChangeUsertext)
END_MESSAGE_MAP()


// TextDlg 메시지 처리기입니다.


void TextDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void TextDlg::OnBnClickedCancel()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
}


void TextDlg::OnEnChangeUserindex()
{
	UpdateData(TRUE);

	if (_ttoi(UserIndex) >= TextMaxIndex)
	{
		UserIndex.Format(_T("%d"), 0);
		CurIndex = UserIndex;
		UpdateData(FALSE);
		return;
	}

	CurText = GameSystem::GetText(_ttoi(UserIndex));
	CurIndex = UserIndex;
	UpdateData(FALSE);
}



void TextDlg::OnBnClickedSavetext()
{
	CString SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"TextData.neet";

	CString BackupData = PathSystem::FindPath(L"TextBackups");

	wchar_t Time[256] = {};

	_itow_s((int)time(nullptr), Time, 36);

	BackupData += L"Backup_";
	BackupData += Time;
	BackupData += L".bak";

	NTWriteStream SaveStream = NTWriteStream(SaveData);
	NTWriteStream BackupStream = NTWriteStream(BackupData);

	int size = TextMaxIndex;
	SaveStream.Write(&size, sizeof(int));
	BackupStream.Write(&size, sizeof(int));

	for (int i = 0; i < size; ++i)
	{
		SaveStream.Write(GameSystem::GetTextData(i), sizeof(wchar_t) * TextMaxBuf);
		BackupStream.Write(GameSystem::GetTextData(i), sizeof(wchar_t) * TextMaxBuf);
	}
}


void TextDlg::OnBnClickedLoadtext()
{
	memset(GameSystem::GetTextData(0), 0, sizeof(wchar_t) * TextMaxIndex * TextMaxBuf);

	CString SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"TextData.neet";

	NTReadStream ReadStream = NTReadStream(SaveData);

	int Count = 0;
	ReadStream.Read(&Count, sizeof(int), sizeof(int));

	for (int i = 0; i < Count; ++i)
	{
		wchar_t TextData[TextMaxBuf] = {};
		ReadStream.Read(TextData, sizeof(TextData), sizeof(TextData));
		GameSystem::SetText(TextData, i);
	}
}

void TextDlg::OnEnChangeUsertext()
{
	UpdateData(TRUE);
	GameSystem::SetText(UserText, _ttoi(CurIndex));
	UpdateData(FALSE);
}

void TextDlg::InitDlg()
{
	Autoptr<NTScene> Scene = NTWinShortCut::GetMainSceneSystem().FindScene(L"TextDlg");
	Autoptr<NTObject> DefaultObj = Scene->CreateObject(L"DefaultObj", 0);

	Autoptr<NTFontRenderer> Help = DefaultObj->AddComponent<NTFontRenderer>(L"궁서");
	Help->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Help->SetSubPivot({ NTWinShortCut::GetMainWindow().GetWidthf() * 0.5f, NTWinShortCut::GetMainWindow().GetHeightf() * 0.5f, 10.0f });
	Help->SetSubScale({ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf(), 1.0f });
	Help->SetSize(50.0f);
	Help->SetString(L"여기 안써요");
	Help->SetColor(255, 255, 255, 255);
	Help->SetFontMode(NTFontRenderer::RENDERMODE::RM_RECT);

	UpdateData(TRUE);
	OnBnClickedLoadtext();
	CurIndex.Format(_T("%d"), 0);
	UserIndex.Format(_T("%d"), 0);
	OnEnChangeUserindex();
	UpdateData(FALSE);
}
