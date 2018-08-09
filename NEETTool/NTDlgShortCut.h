#pragma once
#include <NTScene.h>
#include "ResDlg.h"
#include "MenuDlg.h"
#include "TextDlg.h"
#include "ItemDlg.h"
#include "ItemView.h"

class NTDlgShortCut
{
public:
	static Autoptr<NTScene> SelectScene;
	static MenuDlg* pMenuDlg;
	static ResDlg* pResDlg;
	static TextDlg* pTextDlg;
	static ItemDlg* pItemDlg;
	static ItemView* pItemView;
public:
	NTDlgShortCut();
	~NTDlgShortCut();
};

