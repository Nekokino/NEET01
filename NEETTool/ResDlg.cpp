// ResDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

#include "NTDlgShortCut.h"
#include "NEETTool.h"
#include "ResDlg.h"

#include <ResourceSystem.h>
#include <DebugFunc.h>
#include <NTWinShortCut.h>
#include <NTImage.h>
#include <NTTexture.h>
#include <NTCamera.h>
#include <NTWriteStream.h>
#include <NTReadStream.h>


// ResDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ResDlg, TabDlg)

ResDlg::ResDlg(CWnd* pParent /*=NULL*/)
	: TabDlg(IDD_ResDlg, pParent)
	, SpriteName(_T(""))
	, SliderValue(0)
	, ZoomX(_T(""))
	, ZoomSize(2.0f)
	, ASD(_T(""))
	, UserCutX(_T(""))
	, UserCutY(_T(""))
	, ItemCutX(_T(""))
	, ItemCutY(_T(""))
	, Index(_T(""))
{
	NTDlgShortCut::pResDlg = this;
}

ResDlg::~ResDlg()
{
}

void ResDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ResTree, ResTree);
	DDX_Text(pDX, IDC_SpriteName, SpriteName);
	DDX_Slider(pDX, IDC_ImgSlider, SliderValue);
	DDV_MinMaxInt(pDX, SliderValue, 0, 100);
	DDX_Text(pDX, IDC_MAGNI, ZoomX);
	DDX_Control(pDX, IDC_MAGNI, MagniCtrl);
	DDX_Text(pDX, IDC_AA, ASD);
	DDX_Text(pDX, IDC_USERCUTX, UserCutX);
	DDX_Text(pDX, IDC_USERCUTY, UserCutY);
	DDX_Text(pDX, IDC_ITEMCUTX, ItemCutX);
	DDX_Text(pDX, IDC_ITEMCUTY, ItemCutY);
	DDX_Text(pDX, IDC_INDEX, Index);
}


BEGIN_MESSAGE_MAP(ResDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ResDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ResDlg::OnBnClickedCancel)
	ON_NOTIFY(TVN_SELCHANGED, IDC_ResTree, &ResDlg::OnTvnSelchangedRestree)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_ImgSlider, &ResDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_MAGNI, &ResDlg::OnEnChangeMagni)
	ON_EN_CHANGE(IDC_USERCUTX, &ResDlg::OnEnChangeUsercutx)
	ON_EN_CHANGE(IDC_USERCUTY, &ResDlg::OnEnChangeUsercuty)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SaveButton, &ResDlg::OnBnClickedSavebutton)
	ON_BN_CLICKED(IDC_LoadButton, &ResDlg::OnBnClickedLoadbutton)
	ON_EN_CHANGE(IDC_INDEX, &ResDlg::OnEnChangeIndex)
END_MESSAGE_MAP()


// ResDlg 메시지 처리기입니다.


void ResDlg::OnBnClickedOk()
{
	
}


void ResDlg::OnBnClickedCancel()
{
	
}


BOOL ResDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void ResDlg::InitResDlg()
{
	GetResource(L"Texture", ResTree.InsertItem(L"Texture"));

	Autoptr<NTScene> Scene = NTWinShortCut::GetMainSceneSystem().FindScene(L"ResDlg");
	Autoptr<NTObject> DefaultObj = Scene->CreateObject(L"DefaultObj", 0);
	
	DefaultRenderer = DefaultObj->AddComponent<NTSpRenderer>();
	DefaultObj->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 10.0f });
	DefaultRenderer->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	Scene->GetMainCamera()->SetSMode(NTCamera::SIZEMODE::CSM_CUSTOM);
}

void ResDlg::GetResource(const wchar_t * _Path, HTREEITEM _ParentItem)
{
	std::wstring FindPath = PathSystem::FindPath(_Path);
	std::wstring SearchOp = L"";

	SearchOp = FindPath + L"*.*";

	WIN32_FIND_DATA FindData;
	HANDLE Finder;

	Finder = FindFirstFileW(SearchOp.c_str(), &FindData);

	if (Finder == INVALID_HANDLE_VALUE)
	{
		return;
	}

	while (FindNextFileW(Finder, &FindData))
	{
		if (FindData.dwFileAttributes == 16) //디렉토리인 경우
		{
			if (wcscmp(FindData.cFileName, L"..") == 0) // 상위 디렉토리 한번 찍어줌
			{
				continue;
			}
			else
			{
				std::wstring tmp = _Path;
				tmp += L"\\";
				tmp += FindData.cFileName;

				if (nullptr == PathSystem::FindPath(FindData.cFileName))
				{
					PathSystem::CreatePath(FindData.cFileName, tmp.c_str());
				}

				HTREEITEM FolderItem = ResTree.InsertItem(FindData.cFileName, _ParentItem);
				ResTree.SetItemData(FolderItem, 0);
				GetResource(FindData.cFileName, FolderItem);
			}
		}
		else
		{
			std::unordered_map<std::wstring, NTSpriteData*>::iterator Find = DataMap.find(FindData.cFileName);

			if (Find != DataMap.end())
			{
				if (nullptr == ResourceSystem<NTTexture>::Find(FindData.cFileName))
				{
					ResourceSystem<NTImage>::Load(_Path, FindData.cFileName);
				}
				else
				{
					Autoptr<NTImage> Img = ResourceSystem<NTImage>::Find(FindData.cFileName);
					Img->Cut(Find->second->CutX, Find->second->CutY);
					size_t Index = Img->Cut(NTVEC(0.0f, 0.0f, 1.0f, 1.0f));
					DefaultRenderer->SetImageIndex(Index);
				}

				HTREEITEM Tmp = ResTree.InsertItem(FindData.cFileName, _ParentItem);
				ResTree.SetItemData(Tmp, (DWORD_PTR)Find->second);
			}
			else
			{
				Autoptr<NTImage> Img = ResourceSystem<NTImage>::Load(_Path, FindData.cFileName);

				if (nullptr != Img)
				{
					NTSpriteData* Data = new NTSpriteData();
					lstrcpyW(Data->PathName, _Path);
					lstrcpyW(Data->FileName, FindData.cFileName);

					DataMap.insert(std::unordered_map<std::wstring, NTSpriteData*>::value_type(Data->FileName, Data));

					HTREEITEM Item = ResTree.InsertItem(FindData.cFileName, _ParentItem);
					ResTree.SetItemData(Item, (DWORD_PTR)Data);
				}
			}
		}
	}

	FindClose(Finder);
}


void ResDlg::OnTvnSelchangedRestree(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CString FileName = ResTree.GetItemText(pNMTreeView->itemNew.hItem);
	NTSpriteData* ptr = (NTSpriteData*)ResTree.GetItemData(pNMTreeView->itemNew.hItem);

	UserCutX = L"";
	UserCutY = L"";
	Index = L"0";

	if (ptr != 0)
	{
		CurItem = pNMTreeView->itemNew.hItem;

		CurItemCutX = (size_t)ptr->CutX;
		CurItemCutY = (size_t)ptr->CutY;

		wchar_t Arr[256] = {};
		swprintf_s(Arr, 256, L"%d", CurItemCutX);
		ItemCutX = Arr;

		swprintf_s(Arr, 256, L"%d", CurItemCutY);
		ItemCutY = Arr;

		SliderValue = 50;
		SpriteName = FileName;
		if (true == ptr->IsCut)
		{
			DefaultRenderer->SetImageIndex(ptr->CutX * ptr->CutY);
		}
		else
		{
			DefaultRenderer->SetImageIndex(0);
		}
		
		DefaultRenderer->SetImage(FileName.GetString());
		DefaultRenderer->SetOriginScale();

		if (nullptr != DefaultRenderer->GetImage()->GetTex() || nullptr != DefaultRenderer->GetScene()->GetMainCamera())
		{
			NTVEC2 ImgSize = DefaultRenderer->GetImage()->GetTex()->GetImageSize();
			NTVEC CamSize = DefaultRenderer->GetScene()->GetMainCamera()->GetScreenSize();
			NTVEC2 ScrSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

			if (ImgSize.x / ImgSize.y > CamSize.x / CamSize.y)
			{
				DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize({ ImgSize.x, ImgSize.x * ScrSize.y / ScrSize.x });
			}
			else if (ImgSize.x / ImgSize.y < CamSize.x / CamSize.y)
			{
				DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize({ ImgSize.y * ScrSize.x / ScrSize.y, ImgSize.y });
			}
			else
			{
				DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize({ ImgSize.y, ImgSize.y * ScrSize.y / ScrSize.x });
			}
		}
	}
	else
		CurItem = nullptr;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData(FALSE);
}

void ResDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	float AfterSize;
	if (SliderValue <= 50)
	{
		AfterSize = -ZoomSize / 50.0f * (float)SliderValue + ZoomSize + 1.0f;
	}
	else
	{
		if (ZoomSize > 50.0f && (float)SliderValue < ZoomSize)
		{
			AfterSize = (1.0f / (50.0f - ZoomSize)) * (float)SliderValue + 1.0f - (50.0f / (50.0f - ZoomSize));
		}
		else
			AfterSize = 0.0f;
	}

	
	wchar_t Arr[256] = {};
	swprintf_s(Arr, 256, L"%f", AfterSize);
	ASD = Arr;

	if (AfterSize == 0.0f)
	{
		return;
	}

	if (DefaultRenderer->GetImage() != nullptr)
	{
		NTVEC2 ImgSize = DefaultRenderer->GetImage()->GetTex()->GetImageSize();
		NTVEC CamSize = DefaultRenderer->GetScene()->GetMainCamera()->GetScreenSize();
		NTVEC2 ScrSize = { NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

		if (ImgSize.x / ImgSize.y > CamSize.x / CamSize.y)
		{
			DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize({ ImgSize.x, ImgSize.x * ScrSize.y / ScrSize.x });
		}
		else if (ImgSize.x / ImgSize.y < CamSize.x / CamSize.y)
		{
			DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize({ ImgSize.y * ScrSize.x / ScrSize.y, ImgSize.y });
		}
		else
		{
			DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize({ ImgSize.y, ImgSize.y * ScrSize.y / ScrSize.x });
		}

		NTVEC TmpSize = DefaultRenderer->GetScene()->GetMainCamera()->GetScreenSize();

		DefaultRenderer->GetScene()->GetMainCamera()->SetCustomSize(TmpSize * AfterSize);
	}
	*pResult = 0;
	UpdateData(FALSE);
}



void ResDlg::OnEnChangeMagni()
{
	UpdateData(TRUE);
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// TabDlg::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	MagniCtrl.GetWindowTextW(ZoomX);
	ZoomSize = (float)_wtof(ZoomX);
	if (ZoomSize == 0)
	{
		ZoomSize = 1.0f;
	}
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
}


void ResDlg::OnEnChangeUsercutx()
{
	UpdateData(TRUE);

	if (nullptr == CurItem)
	{
		UpdateData(FALSE);
		return;
	}

	NTSpriteData* SPData = (NTSpriteData*)ResTree.GetItemData(CurItem);
	SPData->CutX = (size_t)_wtoi(UserCutX);

	if (1 > SPData->CutX)
	{
		SPData->CutX = 1;
	}

	DefaultRenderer->GetImage()->Cut(SPData->CutX, SPData->CutY);
	size_t Index = DefaultRenderer->GetImage()->Cut(NTVEC{ 0.0f, 0.0f, 1.0f, 1.0f });
	DefaultRenderer->SetImageIndex(Index);
	SPData->IsCut = true;

	UpdateData(FALSE);
}


void ResDlg::OnEnChangeUsercuty()
{
	UpdateData(TRUE);

	if (nullptr == CurItem)
	{
		UpdateData(FALSE);
		return;
	}

	NTSpriteData* SPData = (NTSpriteData*)ResTree.GetItemData(CurItem);
	SPData->CutY = (size_t)_wtoi(UserCutY);

	if (1 > SPData->CutY)
	{
		SPData->CutY = 1;
	}

	DefaultRenderer->GetImage()->Cut(SPData->CutX, SPData->CutY);
	size_t Index = DefaultRenderer->GetImage()->Cut(NTVEC{ 0.0f, 0.0f, 1.0f, 1.0f });
	DefaultRenderer->SetImageIndex(Index);
	SPData->IsCut = true;

	UpdateData(FALSE);
}


void ResDlg::OnDestroy()
{
	TabDlg::OnDestroy();

	Release();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void ResDlg::OnBnClickedSavebutton()
{
	CString SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"SpriteEditData.neet";

	CString BackupData = PathSystem::FindPath(L"SpriteBackups");
	
	wchar_t Time[256] = {};

	_itow_s((int)time(nullptr), Time, 36);

	BackupData += L"Backup_";
	BackupData += Time;
	BackupData += L".bak";

	NTWriteStream SaveStream = NTWriteStream(SaveData);
	NTWriteStream BackupStream = NTWriteStream(BackupData);

	int size = (int)DataMap.size();
	SaveStream.Write(&size, sizeof(int));
	BackupStream.Write(&size, sizeof(int));

	std::unordered_map<std::wstring, NTSpriteData*>::iterator StartIter = DataMap.begin();
	std::unordered_map<std::wstring, NTSpriteData*>::iterator EndIter = DataMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		NTSpriteData* SaveData = StartIter->second;

		SaveStream.Write(SaveData, sizeof(NTSpriteData));
		BackupStream.Write(SaveData, sizeof(NTSpriteData));
	}
}


void ResDlg::OnBnClickedLoadbutton()
{
	Release();
	ResTree.DeleteAllItems();

	CString SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"SpriteEditData.neet";

	NTReadStream ReadStream = NTReadStream(SaveData);

	int Count = 0;
	ReadStream.Read(&Count, sizeof(int), sizeof(int));

	for (int i = 0; i < Count; ++i)
	{
		NTSpriteData* Data = new NTSpriteData();

		ReadStream.Read(Data, sizeof(NTSpriteData), sizeof(NTSpriteData));
		DataMap.insert(std::unordered_map<std::wstring, NTSpriteData*>::value_type(Data->FileName, Data));
	}

	GetResource(L"Texture", ResTree.InsertItem(L"Texture"));
}

void ResDlg::Release()
{
	std::unordered_map<std::wstring, NTSpriteData*>::iterator StartIter = DataMap.begin();
	std::unordered_map<std::wstring, NTSpriteData*>::iterator EndIter = DataMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		delete StartIter->second;
	}

	DataMap.clear();
}

void ResDlg::OnEnChangeIndex()
{
	UpdateData(TRUE);

	if (CurItem == nullptr)
	{
		UpdateData(FALSE);
		return;
	}

	size_t CheckIndex = (size_t)_wtoi(Index);

	if (CheckIndex >= DefaultRenderer->GetImage()->GetCutCount())
	{
		Index = L"SIZE OVER!!";
		CheckIndex = DefaultRenderer->GetImage()->GetCutCount() - 1;
	}

	

	DefaultRenderer->SetImageIndex(CheckIndex);
	UpdateData(FALSE);
}
