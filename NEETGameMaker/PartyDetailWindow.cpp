#include "PartyDetailWindow.h"

#include <NTSpRenderer.h>
#include <NTFontRenderer.h>
#include <NTWinShortCut.h>

#include "NTPieceWindow.h"


PartyDetailWindow::PartyDetailWindow() : Index(0), WinSize(0.0f), CurCharacter(CHARA_MAX),
	CharacterFace(nullptr), CharacterElement(nullptr), CharacterLevel(nullptr), CharacterName(nullptr),
	EquipAcc(nullptr), EquipHelmet(nullptr), Power(nullptr), Hit(nullptr),
	Speed(nullptr), Magic(nullptr), Evade(nullptr), Stamina(nullptr), MagicDef(nullptr), CurExp(nullptr),
	NextExp(nullptr), WeaponIcon(nullptr)
{
}


PartyDetailWindow::~PartyDetailWindow()
{
}

bool PartyDetailWindow::Init(int _Index)
{
	Index = _Index;
	SetPlayerStatus(Index);

	WinSize = NTVEC2{ NTWinShortCut::GetMainWindow().GetWidthf(), NTWinShortCut::GetMainWindow().GetHeightf() };

	Autoptr<NTPieceWindow> ActualWin05 = GetNTObject()->AddComponent<NTPieceWindow>(8, 12, 0.5035f);
	GetNTObject()->GetTransform()->SetLocalPosition({ WinSize.x * 0.15f, 0.0f });

	CharacterFace = GetNTObject()->AddComponent<NTSpRenderer>(UILayer);
	CharacterFace->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	CharacterFace->SetImageIndex(0);
	CharacterFace->SetSubScale({ 192.0f, 192.0f, 1.0f });
	CharacterFace->SetSubPivot({ WinSize.x * -0.125f, WinSize.y * 0.3f });

	CharacterElement = GetNTObject()->AddComponent<NTSpRenderer>(UILayer);
	CharacterElement->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	CharacterElement->SetImageIndex(1);
	CharacterElement->SetSubScale({ 192.0f, 192.0f, 1.0f });
	CharacterElement->SetSubPivot({ WinSize.x * 0.05f, WinSize.y * 0.3f + 64.0f });

	CharacterName = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	CharacterName->SetColor(255, 255, 255, 255);
	CharacterName->SetSubPivot({ WinSize.x * 0.0f, WinSize.y * 0.0f });
	CharacterName->SetSubScale({ 1.0f, 1.0f, 1.0f });
	CharacterName->SetSize(25.0f);
	CharacterName->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	CharacterName->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	CharacterLevel = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	CharacterLevel->SetColor(255, 255, 255, 255);
	CharacterLevel->SetSubPivot({ WinSize.x * 0.67f, WinSize.y * 0.275f });
	CharacterLevel->SetSubScale({ 1.0f, 1.0f, 1.0f });
	CharacterLevel->SetSize(25.0f);
	CharacterLevel->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	CharacterLevel->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	//tmp.clear();
	//tmp = L"LEVEL ";
	//_itow_s(GameSystem::GetBattlememberStatus(0).Level, tmpbuf, 10);
	//tmp += tmpbuf;
	//CharacterLevel->SetString(tmp.c_str()); // ³ªÁß¿¡ ¹Ù²ã¾ßµÊ

	Autoptr<NTFontRenderer> PlaneEquipText = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneEquipText->SetColor(255, 255, 255, 255);
	PlaneEquipText->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.34f });
	PlaneEquipText->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneEquipText->SetSize(25.0f);
	PlaneEquipText->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneEquipText->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneEquipText->SetString(L"Àå     ºñ");

	EqiupWeapon = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EqiupWeapon->SetColor(255, 255, 255, 255);
	EqiupWeapon->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.34f });
	EqiupWeapon->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EqiupWeapon->SetSize(25.0f);
	EqiupWeapon->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EqiupWeapon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	WeaponIcon = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	WeaponIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	WeaponIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * 0.14f });
	//WeaponIcon->SetImageIndex(0);
	WeaponIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT); // ¹«±â¿¡ µû¶ó ¹Ù²ãÁà¾ßÇÔ

	EquipHelmet = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EquipHelmet->SetColor(255, 255, 255, 255);
	EquipHelmet->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.39f });
	EquipHelmet->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipHelmet->SetSize(25.0f);
	EquipHelmet->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipHelmet->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTSpRenderer> HelmetIcon = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	HelmetIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	HelmetIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * 0.09f });
	HelmetIcon->SetImageIndex(7);
	HelmetIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);


	EquipArmor = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EquipArmor->SetColor(255, 255, 255, 255);
	EquipArmor->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.44f });
	EquipArmor->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipArmor->SetSize(25.0f);
	EquipArmor->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipArmor->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTSpRenderer> ArmorIcon = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	ArmorIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	ArmorIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * 0.04f });
	ArmorIcon->SetImageIndex(8);
	ArmorIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	EquipAcc = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	EquipAcc->SetColor(255, 255, 255, 255);
	EquipAcc->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.49f });
	EquipAcc->SetSubScale({ 1.0f, 1.0f, 1.0f });
	EquipAcc->SetSize(25.0f);
	EquipAcc->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	EquipAcc->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTSpRenderer> AccIcon = GetNTObject()->AddComponent<NTSpRenderer>(L"SmallIcon.png", UILayer);
	AccIcon->SetSubScale({ 32.0f, 32.0f, 1.0f });
	AccIcon->SetSubPivot({ -WinSize.x * 0.025f, WinSize.y * -0.01f });
	AccIcon->SetImageIndex(9);
	AccIcon->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlanePower = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlanePower->SetColor(255, 255, 255, 255);
	PlanePower->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.575f });
	PlanePower->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlanePower->SetSize(25.0f);
	PlanePower->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlanePower->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlanePower->SetString(L"Èû");

	Power = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Power->SetColor(255, 255, 255, 255);
	Power->SetSubPivot({ WinSize.x * 0.575f, WinSize.y * 0.575f });
	Power->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Power->SetSize(25.0f);
	Power->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Power->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneHit = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneHit->SetColor(255, 255, 255, 255);
	PlaneHit->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.575f });
	PlaneHit->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneHit->SetSize(25.0f);
	PlaneHit->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneHit->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneHit->SetString(L"¸íÁß");

	Hit = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Hit->SetColor(255, 255, 255, 255);
	Hit->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.575f });
	Hit->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Hit->SetSize(25.0f);
	Hit->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Hit->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneSpeed = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneSpeed->SetColor(255, 255, 255, 255);
	PlaneSpeed->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.625f });
	PlaneSpeed->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneSpeed->SetSize(25.0f);
	PlaneSpeed->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneSpeed->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneSpeed->SetString(L"¼Óµµ");

	Speed = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Speed->SetColor(255, 255, 255, 255);
	Speed->SetSubPivot({ WinSize.x * 0.575f, WinSize.y * 0.625f });
	Speed->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Speed->SetSize(25.0f);
	Speed->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Speed->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneMagic = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneMagic->SetColor(255, 255, 255, 255);
	PlaneMagic->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.625f });
	PlaneMagic->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneMagic->SetSize(25.0f);
	PlaneMagic->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneMagic->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneMagic->SetString(L"¸¶¹ý");

	Magic = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Magic->SetColor(255, 255, 255, 255);
	Magic->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.625f });
	Magic->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Magic->SetSize(25.0f);
	Magic->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Magic->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneEvade = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneEvade->SetColor(255, 255, 255, 255);
	PlaneEvade->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.675f });
	PlaneEvade->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneEvade->SetSize(25.0f);
	PlaneEvade->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneEvade->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneEvade->SetString(L"È¸ÇÇ");

	Evade = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Evade->SetColor(255, 255, 255, 255);
	Evade->SetSubPivot({ WinSize.x * 0.575f, WinSize.y * 0.675f });
	Evade->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Evade->SetSize(25.0f);
	Evade->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Evade->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneStamina = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneStamina->SetColor(255, 255, 255, 255);
	PlaneStamina->SetSubPivot({ WinSize.x * 0.65f, WinSize.y * 0.675f });
	PlaneStamina->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneStamina->SetSize(25.0f);
	PlaneStamina->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneStamina->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneStamina->SetString(L"Ã¼·Â");

	Stamina = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	Stamina->SetColor(255, 255, 255, 255);
	Stamina->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.675f });
	Stamina->SetSubScale({ 1.0f, 1.0f, 1.0f });
	Stamina->SetSize(25.0f);
	Stamina->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	Stamina->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneMagicDef = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneMagicDef->SetColor(255, 255, 255, 255);
	PlaneMagicDef->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.725f });
	PlaneMagicDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneMagicDef->SetSize(25.0f);
	PlaneMagicDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneMagicDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneMagicDef->SetString(L"¸¶¹ý ¹æ¾î·Â");

	MagicDef = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	MagicDef->SetColor(255, 255, 255, 255);
	MagicDef->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.725f });
	MagicDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	MagicDef->SetSize(25.0f);
	MagicDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	MagicDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneCurExp = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneMagicDef->SetColor(255, 255, 255, 255);
	PlaneMagicDef->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.8f });
	PlaneMagicDef->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneMagicDef->SetSize(25.0f);
	PlaneMagicDef->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneMagicDef->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneMagicDef->SetString(L"ÇöÀç °æÇèÄ¡");

	CurExp = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	CurExp->SetColor(255, 255, 255, 255);
	CurExp->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.8f });
	CurExp->SetSubScale({ 1.0f, 1.0f, 1.0f });
	CurExp->SetSize(25.0f);
	CurExp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	CurExp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	Autoptr<NTFontRenderer> PlaneNextExp = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	PlaneNextExp->SetColor(255, 255, 255, 255);
	PlaneNextExp->SetSubPivot({ WinSize.x * 0.43f, WinSize.y * 0.85f });
	PlaneNextExp->SetSubScale({ 1.0f, 1.0f, 1.0f });
	PlaneNextExp->SetSize(25.0f);
	PlaneNextExp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	PlaneNextExp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	PlaneNextExp->SetString(L"´ÙÀ½ ·¹º§¾÷");

	NextExp = GetNTObject()->AddComponent<NTFontRenderer>(L"±Ã¼­", UILayer);
	NextExp->SetColor(255, 255, 255, 255);
	NextExp->SetSubPivot({ WinSize.x * 0.8f, WinSize.y * 0.85f });
	NextExp->SetSubScale({ 1.0f, 1.0f, 1.0f });
	NextExp->SetSize(25.0f);
	NextExp->SetFontMode(NTFontRenderer::RENDERMODE::RM_NORMAL);
	NextExp->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	return true;
}

void PartyDetailWindow::MainUpdate()
{
	SetPlayerStatus(Index);

	switch (CurCharacter)
	{
	case CHRONO:
		CharacterFace->SetImage(L"Chrono_UI.png");
		CharacterElement->SetImage(L"Chrono_UI.png");
		WeaponIcon->SetImageIndex(0);
		break;
	case LUCCA:
		CharacterFace->SetImage(L"Lucca_UI.png");
		CharacterElement->SetImage(L"Lucca_UI.png");
		WeaponIcon->SetImageIndex(2);
		break;
	case MARU:
		CharacterFace->SetImage(L"Maru_UI.png");
		CharacterElement->SetImage(L"Maru_UI.png");
		WeaponIcon->SetImageIndex(1);
		break;
	case KAERU:
		CharacterFace->SetImage(L"Kaeru_UI.png");
		CharacterElement->SetImage(L"Kaeru_UI.png");
		WeaponIcon->SetImageIndex(4);
		break;
	case ROBO:
		CharacterFace->SetImage(L"Robo_UI.png");
		CharacterElement->SetImage(L"Robo_UI.png");
		WeaponIcon->SetImageIndex(3);
		break;
	case EIRA:
		CharacterFace->SetImage(L"Eira_UI.png");
		CharacterElement->SetImage(L"Eira_UI.png");
		WeaponIcon->SetImageIndex(5);
		break;
	case MAOU:
		CharacterFace->SetImage(L"Maou_UI.png");
		CharacterElement->SetImage(L"Maou_UI.png");
		WeaponIcon->SetImageIndex(6);
		break;
	case CHARA_MAX:
		return;
		break;
	default:
		return;
		break;
	}
	
	std::wstring TmpStr;
	wchar_t TmpBuf[32];

	CharacterName->SetString(CurStatus->Name);
	TmpStr.clear();
	swprintf_s(TmpBuf, L"LEVEL %d", CurStatus->Level);
	TmpStr += TmpBuf;
	CharacterLevel->SetString(TmpStr.c_str());
	EqiupWeapon->SetString(CurStatus->Weapon.Output.c_str());
	EquipHelmet->SetString(CurStatus->Helmet.Output.c_str());
	EquipArmor->SetString(CurStatus->Armor.Output.c_str());
	EquipAcc->SetString(CurStatus->Acc.Output.c_str());
	

	wchar_t Buf[32];

	Power->SetString(IntToString(Buf, CurStatus->Power));
	Hit->SetString(IntToString(Buf, CurStatus->Hit));
	Speed->SetString(IntToString(Buf, CurStatus->Speed));
	Magic->SetString(IntToString(Buf, CurStatus->Magic));
	Evade->SetString(IntToString(Buf, CurStatus->Evade));
	Stamina->SetString(IntToString(Buf, CurStatus->Stamina));
	MagicDef->SetString(IntToString(Buf, CurStatus->MagicDef));
	CurExp->SetString(IntToString(Buf, CurStatus->CurEXP));
	NextExp->SetString(IntToString(Buf, CurStatus->NextEXP));
}

void PartyDetailWindow::DbgRender()
{
}