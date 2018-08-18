#include "PartyWindow.h"

#include "NTPieceWindow.h"
#include "GameSystem.h"

#include <NTWinShortCut.h>
#include <NTFontRenderer.h>
#include <NTSpRenderer.h>

PartyWindow::PartyWindow()
{
}


PartyWindow::~PartyWindow()
{
}

bool PartyWindow::Init()
{
	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	LeftWindow01 = GetScene()->CreateObject(L"Window01", UILayer);
	GetNTObject()->AddChild(LeftWindow01);
	Autoptr<NTPieceWindow> ActualWin01 = LeftWindow01->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	LeftWindow01->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * 0.3375f });

	Autoptr<NTFontRenderer> Name01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Name01->SetColor(255, 255, 255, 255);
	Name01->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f, 1.0f });
	Name01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Name01->SetSize(25.0f);
	Name01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Name01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	Name01->SetString(GameSystem::GetBattlememberStatus(0).Name);

	Autoptr<NTFontRenderer> Level01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Level01->SetColor(255, 255, 255, 255);
	Level01->SetSubPivot({ WinSize.x * 0.275f, WinSize.y * 0.065f, 1.0f });
	Level01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Level01->SetSize(25.0f);
	Level01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Level01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	std::wstring tmp = Level01->GetString();
	tmp = L"Lv    ";
	wchar_t tmpbuf[32];
	_itow_s(GameSystem::GetBattlememberStatus(0).Level, tmpbuf, 10);
	if (GameSystem::GetBattlememberStatus(0).Level < 10)
	{
		tmp += L"  ";
	}
	tmp += tmpbuf;
	Level01->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlainHP01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainHP01->SetColor(255, 255, 255, 255);
	PlainHP01->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f + 30.0f, 1.0f });
	PlainHP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainHP01->SetSize(25.0f);
	PlainHP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainHP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainHP01->SetString(L"HP");

	Autoptr<NTFontRenderer> HP01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	HP01->SetColor(255, 255, 255, 255);
	HP01->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.065f + 30.0f, 1.0f });
	HP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	HP01->SetSize(25.0f);
	HP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	HP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).CurHP, tmpbuf, 10);
	tmp += tmpbuf;
	tmp += L" / ";
	_itow_s(GameSystem::GetBattlememberStatus(0).MaxHP, tmpbuf, 10);
	tmp += tmpbuf;
	int tmpint = 11 - lstrlenW(tmp.c_str());
	switch (tmpint)
	{
	case 3:
		tmp.insert(0, L"  ");
		break;
	case 4:
		tmp.insert(0, L"   ");
		break;
	case 5:
		tmp.insert(0, L"     ");
		break;
	case 6:
		tmp.insert(0, L"       ");
		break;
	default:
		break;
	}
	HP01->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlainMP01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlainMP01->SetColor(255, 255, 255, 255);
	PlainMP01->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.065f + 60.0f, 1.0f });
	PlainMP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlainMP01->SetSize(25.0f);
	PlainMP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlainMP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlainMP01->SetString(L"MP");

	Autoptr<NTFontRenderer> MP01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MP01->SetColor(255, 255, 255, 255);
	MP01->SetSubPivot({ WinSize.x * 0.2625f, WinSize.y * 0.065f + 60.0f, 1.0f });
	MP01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MP01->SetSize(25.0f);
	MP01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MP01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).CurMP, tmpbuf, 10);
	tmp += tmpbuf;
	tmp += L" / ";
	_itow_s(GameSystem::GetBattlememberStatus(0).MaxMP, tmpbuf, 10);
	tmp += tmpbuf;
	tmpint = 11 - lstrlenW(tmp.c_str());
	switch (tmpint)
	{
	case 3:
		tmp.insert(0, L"  ");
		break;
	case 4:
		tmp.insert(0, L"   ");
		break;
	case 5:
		tmp.insert(0, L"     ");
		break;
	case 6:
		tmp.insert(0, L"      ");
		break;
	default:
		break;
	}
	MP01->SetString(tmp.c_str());

	Autoptr<NTSpRenderer> PlaneAtk01 = LeftWindow01->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	PlaneAtk01->SetSubScale({ 32.0f, 32.0f, 1.0f });
	PlaneAtk01->SetSubPivot({ -WinSize.x * 0.115f, -WinSize.y * 0.065f });
	PlaneAtk01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> Atk01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Atk01->SetColor(255, 255, 255, 255);
	Atk01->SetSubPivot({ WinSize.x * 0.175f, WinSize.y * 0.21f });
	Atk01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Atk01->SetSize(25.0f);
	Atk01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Atk01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	int Damage = GameSystem::GetBattlememberStatus(0).Power + GameSystem::GetBattlememberStatus(0).Weapon.Atk;
	_itow_s(Damage, tmpbuf, 10);
	tmp += tmpbuf;
	Atk01->SetString(tmp.c_str());

	Autoptr<NTSpRenderer> PlaneDef01 = LeftWindow01->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	PlaneDef01->SetSubScale({ 32.0f, 32.0f, 1.0f });
	PlaneDef01->SetSubPivot({ WinSize.x * 0.025f, -WinSize.y * 0.065f });
	PlaneDef01->SetImageIndex(14);
	PlaneDef01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> Def01 = LeftWindow01->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Def01->SetColor(255, 255, 255, 255);
	Def01->SetSubPivot({ WinSize.x * 0.325f, WinSize.y * 0.21f });
	Def01->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Def01->SetSize(25.0f);
	Def01->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Def01->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	int Defence = GameSystem::GetBattlememberStatus(0).Stamina + GameSystem::GetBattlememberStatus(0).Armor.Def + GameSystem::GetBattlememberStatus(0).Helmet.Def;
	_itow_s(Defence, tmpbuf, 10);
	tmp += tmpbuf;
	Def01->SetString(tmp.c_str());

	Autoptr<NTObject> Window02 = GetScene()->CreateObject(L"Window02", UILayer);
	GetNTObject()->AddChild(Window02);
	Autoptr<NTPieceWindow> ActualWin02 = Window02->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	Window02->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * 0.1125f });

	Autoptr<NTObject> Window03 = GetScene()->CreateObject(L"Window03", UILayer);
	GetNTObject()->AddChild(Window03);
	Autoptr<NTPieceWindow> ActualWin03 = Window03->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	Window03->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.1125f });

	Autoptr<NTObject> Window04 = GetScene()->CreateObject(L"Window04", UILayer);
	GetNTObject()->AddChild(Window04);
	Autoptr<NTPieceWindow> ActualWin04 = Window04->AddComponent<NTPieceWindow>(5, 3, 0.45f);
	Window04->GetTransform()->SetLocalPosition({ WinSize.x * -0.27f, WinSize.y * -0.3375f });

	Autoptr<NTFontRenderer> PlanePlayTime = Window04->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlanePlayTime->SetColor(255, 255, 255, 255);
	PlanePlayTime->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.775f });
	PlanePlayTime->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlanePlayTime->SetSize(25.0f);
	PlanePlayTime->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlanePlayTime->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlanePlayTime->SetString(L"PlayTime");

	Autoptr<NTFontRenderer> PlayTime = Window04->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlayTime->SetColor(255, 255, 255, 255);
	PlayTime->SetSubPivot({ WinSize.x * 0.235f, WinSize.y * 0.775f });
	PlayTime->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlayTime->SetSize(25.0f);
	PlayTime->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlayTime->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	swprintf_s(tmpbuf, L"%f", GameSystem::GetPlayTime()); // ¾÷µ¥ÀÌÆ®¿¡¼­ ÇØÁà¾ßÇÔ.
	tmp += tmpbuf;
	PlayTime->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneGold = Window04->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneGold->SetColor(255, 255, 255, 255);
	PlaneGold->SetSubPivot({ WinSize.x * 0.1f, WinSize.y * 0.85f });
	PlaneGold->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneGold->SetSize(25.0f);
	PlaneGold->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneGold->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneGold->SetString(L"Gold");

	Autoptr<NTFontRenderer> Gold = Window04->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Gold->SetColor(255, 255, 255, 255);
	Gold->SetSubPivot({ WinSize.x * 0.235f, WinSize.y * 0.85f });
	Gold->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Gold->SetSize(25.0f);
	Gold->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Gold->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	swprintf_s(tmpbuf, L"%d", GameSystem::GetGold()); // ¾÷µ¥ÀÌÆ®¿¡¼­ ÇØÁà¾ßÇÔ.
	tmp += tmpbuf;
	Gold->SetString(tmp.c_str());

	Autoptr<NTObject> Window05 = GetScene()->CreateObject(L"Window05", UILayer);
	GetNTObject()->AddChild(Window05);
	Autoptr<NTPieceWindow> ActualWin05 = Window05->AddComponent<NTPieceWindow>(8, 12, 0.5035f);
	Window05->GetTransform()->SetLocalPosition({ WinSize.x * 0.15f, 0.0f });

	Autoptr<NTSpRenderer> CharacterFace = Window05->AddComponent<NTSpRenderer>(L"Kaeru_UI.png", UILayer);
	CharacterFace->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	CharacterFace->SetImageIndex(0);
	CharacterFace->SetSubScale({ 192.0f, 192.0f, 1.0f });
	CharacterFace->SetSubPivot({ WinSize.x * -0.125f, WinSize.y * 0.3f });

	Autoptr<NTSpRenderer> CharacterElement = Window05->AddComponent<NTSpRenderer>(L"Kaeru_UI.png", UILayer);
	CharacterElement->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	CharacterElement->SetImageIndex(1);
	CharacterElement->SetSubScale({ 192.0f, 192.0f, 1.0f });
	CharacterElement->SetSubPivot({ WinSize.x * 0.05f, WinSize.y * 0.3f + 64.0f });

	Autoptr<NTFontRenderer> CharacterName = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	CharacterName->SetColor(255, 255, 255, 255);
	CharacterName->SetSubPivot({ WinSize.x * 0.67f, WinSize.y * 0.2f });
	CharacterName->SetSubScale({ 1.0f, 1.0f, 1.0f });
	CharacterName->SetSize(25.0f);
	CharacterName->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	CharacterName->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	CharacterName->SetString(GameSystem::GetBattlememberStatus(0).Name); // ³ªÁß¿¡ ¹Ù²ã¾ßµÊ

	Autoptr<NTFontRenderer> CharacterLevel = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	CharacterLevel->SetColor(255, 255, 255, 255);
	CharacterLevel->SetSubPivot({ WinSize.x * 0.67f, WinSize.y * 0.275f });
	CharacterLevel->SetSubScale({ 1.0f, 1.0f, 1.0f });
	CharacterLevel->SetSize(25.0f);
	CharacterLevel->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	CharacterLevel->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	tmp = L"LEVEL ";
	_itow_s(GameSystem::GetBattlememberStatus(0).Level, tmpbuf, 10);
	tmp += tmpbuf;
	CharacterLevel->SetString(tmp.c_str()); // ³ªÁß¿¡ ¹Ù²ã¾ßµÊ

	Autoptr<NTFontRenderer> PlaneEquipText = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneEquipText->SetColor(255, 255, 255, 255);
	PlaneEquipText->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.34f });
	PlaneEquipText->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneEquipText->SetSize(25.0f);
	PlaneEquipText->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneEquipText->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneEquipText->SetString(L"Àå     ºñ");

	Autoptr<NTFontRenderer> EqiupWeapon = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EqiupWeapon->SetColor(255, 255, 255, 255);
	EqiupWeapon->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.34f });
	EqiupWeapon->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EqiupWeapon->SetSize(25.0f);
	EqiupWeapon->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EqiupWeapon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	EqiupWeapon->SetString(GameSystem::GetBattlememberStatus(0).Weapon.Output.c_str());

	Autoptr<NTSpRenderer> WeaponIcon = Window05->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	WeaponIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	WeaponIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * 0.14f });
	WeaponIcon->SetImageIndex(0);
	WeaponIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT); // ¹«±â¿¡ µû¶ó ¹Ù²ãÁà¾ßÇÔ

	Autoptr<NTFontRenderer> EquipHelmet = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EquipHelmet->SetColor(255, 255, 255, 255);
	EquipHelmet->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.39f });
	EquipHelmet->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipHelmet->SetSize(25.0f);
	EquipHelmet->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipHelmet->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	EquipHelmet->SetString(GameSystem::GetBattlememberStatus(0).Helmet.Output.c_str());

	Autoptr<NTSpRenderer> HelmetIcon = Window05->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	HelmetIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	HelmetIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * 0.09f });
	HelmetIcon->SetImageIndex(7);
	HelmetIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);


	Autoptr<NTFontRenderer> EquipArmor = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EquipArmor->SetColor(255, 255, 255, 255);
	EquipArmor->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.44f });
	EquipArmor->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipArmor->SetSize(25.0f);
	EquipArmor->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipArmor->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	EquipArmor->SetString(GameSystem::GetBattlememberStatus(0).Armor.Output.c_str());

	Autoptr<NTSpRenderer> ArmorIcon = Window05->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	ArmorIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	ArmorIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * 0.04f });
	ArmorIcon->SetImageIndex(8);
	ArmorIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> EquipAcc = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EquipAcc->SetColor(255, 255, 255, 255);
	EquipAcc->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.49f });
	EquipAcc->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipAcc->SetSize(25.0f);
	EquipAcc->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipAcc->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	EquipAcc->SetString(GameSystem::GetBattlememberStatus(0).Acc.Output.c_str());

	Autoptr<NTSpRenderer> AccIcon = Window05->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	AccIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	AccIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * -0.01f });
	AccIcon->SetImageIndex(9);
	AccIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlanePower = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlanePower->SetColor(255, 255, 255, 255);
	PlanePower->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.575f });
	PlanePower->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlanePower->SetSize(25.0f);
	PlanePower->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlanePower->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlanePower->SetString(L"Èû");

	Autoptr<NTFontRenderer> Power = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Power->SetColor(255, 255, 255, 255);
	Power->SetSubPivot({ WinSize.x * 0.575f, WinSize.y * 0.575f });
	Power->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Power->SetSize(25.0f);
	Power->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Power->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).Power, tmpbuf, 10);
	tmp += tmpbuf;
	Power->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneHit = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneHit->SetColor(255, 255, 255, 255);
	PlaneHit->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.575f });
	PlaneHit->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneHit->SetSize(25.0f);
	PlaneHit->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneHit->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneHit->SetString(L"¸íÁß");

	Autoptr<NTFontRenderer> Hit = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Hit->SetColor(255, 255, 255, 255);
	Hit->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.575f });
	Hit->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Hit->SetSize(25.0f);
	Hit->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Hit->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).Hit, tmpbuf, 10);
	tmp += tmpbuf;
	Hit->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneSpeed = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneSpeed->SetColor(255, 255, 255, 255);
	PlaneSpeed->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.625f });
	PlaneSpeed->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneSpeed->SetSize(25.0f);
	PlaneSpeed->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneSpeed->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneSpeed->SetString(L"¼Óµµ");

	Autoptr<NTFontRenderer> Speed = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Speed->SetColor(255, 255, 255, 255);
	Speed->SetSubPivot({ WinSize.x * 0.575f, WinSize.y * 0.625f });
	Speed->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Speed->SetSize(25.0f);
	Speed->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Speed->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).Speed, tmpbuf, 10);
	tmp += tmpbuf;
	Speed->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneMagic = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneMagic->SetColor(255, 255, 255, 255);
	PlaneMagic->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.625f });
	PlaneMagic->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneMagic->SetSize(25.0f);
	PlaneMagic->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneMagic->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneMagic->SetString(L"¸¶¹ý");

	Autoptr<NTFontRenderer> Magic = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Magic->SetColor(255, 255, 255, 255);
	Magic->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.625f });
	Magic->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Magic->SetSize(25.0f);
	Magic->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Magic->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).Magic, tmpbuf, 10);
	tmp += tmpbuf;
	Magic->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneEvade = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneEvade->SetColor(255, 255, 255, 255);
	PlaneEvade->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.675f });
	PlaneEvade->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneEvade->SetSize(25.0f);
	PlaneEvade->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneEvade->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneEvade->SetString(L"È¸ÇÇ");

	Autoptr<NTFontRenderer> Evade = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Evade->SetColor(255, 255, 255, 255);
	Evade->SetSubPivot({ WinSize.x * 0.575f, WinSize.y * 0.675f });
	Evade->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Evade->SetSize(25.0f);
	Evade->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Evade->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).Evade, tmpbuf, 10);
	tmp += tmpbuf;
	Evade->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneStamina = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneStamina->SetColor(255, 255, 255, 255);
	PlaneStamina->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.675f });
	PlaneStamina->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneStamina->SetSize(25.0f);
	PlaneStamina->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneStamina->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneStamina->SetString(L"Ã¼·Â");

	Autoptr<NTFontRenderer> Stamina = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Stamina->SetColor(255, 255, 255, 255);
	Stamina->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.675f });
	Stamina->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Stamina->SetSize(25.0f);
	Stamina->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Stamina->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).Stamina, tmpbuf, 10);
	tmp += tmpbuf;
	Stamina->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneMagicDef = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneMagicDef->SetColor(255, 255, 255, 255);
	PlaneMagicDef->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.725f });
	PlaneMagicDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneMagicDef->SetSize(25.0f);
	PlaneMagicDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneMagicDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneMagicDef->SetString(L"¸¶¹ý ¹æ¾î·Â");

	Autoptr<NTFontRenderer> MagicDef = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MagicDef->SetColor(255, 255, 255, 255);
	MagicDef->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.725f });
	MagicDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MagicDef->SetSize(25.0f);
	MagicDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MagicDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).MagicDef, tmpbuf, 10);
	tmp += tmpbuf;
	MagicDef->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneCurExp = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneMagicDef->SetColor(255, 255, 255, 255);
	PlaneMagicDef->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.8f });
	PlaneMagicDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneMagicDef->SetSize(25.0f);
	PlaneMagicDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneMagicDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneMagicDef->SetString(L"ÇöÀç °æÇèÄ¡");

	Autoptr<NTFontRenderer> CurExp = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	CurExp->SetColor(255, 255, 255, 255);
	CurExp->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.8f });
	CurExp->SetSubScale({ 1.0f, 1.0f, 1.0f });
	CurExp->SetSize(25.0f);
	CurExp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	CurExp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).CurEXP, tmpbuf, 10);
	tmp += tmpbuf;
	CurExp->SetString(tmp.c_str());

	Autoptr<NTFontRenderer> PlaneNextExp = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneNextExp->SetColor(255, 255, 255, 255);
	PlaneNextExp->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.85f });
	PlaneNextExp->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneNextExp->SetSize(25.0f);
	PlaneNextExp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneNextExp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneNextExp->SetString(L"´ÙÀ½ ·¹º§¾÷");

	Autoptr<NTFontRenderer> NextExp = Window05->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	NextExp->SetColor(255, 255, 255, 255);
	NextExp->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.85f });
	NextExp->SetSubScale({ 1.0f, 1.0f, 1.0f });
	NextExp->SetSize(25.0f);
	NextExp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	NextExp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	tmp.clear();
	_itow_s(GameSystem::GetBattlememberStatus(0).NextEXP, tmpbuf, 10);
	tmp += tmpbuf;
	NextExp->SetString(tmp.c_str());

	return true;
}

void PartyWindow::MainUpdate()
{
}

void PartyWindow::DbgRender()
{
}