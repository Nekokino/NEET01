#include "NTField.h"
#include <NTSpRenderer.h>
#include <NTSpFrameAnimator.h>
#include <CustomMacro.h>
#include <NTWinShortCut.h>
#include "NTEvent.h"
#include "GameSystem.h"
#include "NTNPC.h"
#include "NTBattle.h"
#include "NTEnemy.h"

std::unordered_map<std::wstring, FieldData> NTField::FieldMap = std::unordered_map<std::wstring, FieldData>();

NTField::NTField() : FieldImage(nullptr), ColImage(nullptr), MapSize(0.0f)
{

}


NTField::~NTField()
{
	std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator ObjStartIter = FieldObjMap.begin();
	std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator ObjEndIter = FieldObjMap.end();

	for (; ObjStartIter != ObjEndIter; ++ObjStartIter)
	{
		ObjStartIter->second->Death();
	}

	std::unordered_map<std::wstring, Autoptr<NTEvent>>::iterator EventStartIter = FieldEventMap.begin();
	std::unordered_map<std::wstring, Autoptr<NTEvent>>::iterator EventEndIter = FieldEventMap.end();

	for (; EventStartIter != EventEndIter; ++EventStartIter)
	{
		EventStartIter->second->Death();
	}

	std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator NPCStartIter = FieldNPCMap.begin();
	std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator NPCEndIter = FieldNPCMap.end();

	for (; NPCStartIter != NPCEndIter; ++NPCStartIter)
	{
		NPCStartIter->second->Death();
	}
}

FieldData NTField::FindFieldData(const wchar_t * _Key)
{
	std::unordered_map<std::wstring, FieldData>::iterator FindIter = FieldMap.find(_Key);

	if (FindIter == FieldMap.end())
	{
		tassert(true);
		return FieldData();
	}

	return FindIter->second;
}

void NTField::DefaultDataSet()
{
	std::wstring TempKey;

	
	NTVEC Vector;

	TempKey.clear();
	TempKey = L"";
#pragma region Leene_Center Init
	FieldData* NewData = new FieldData();
	lstrcpyW(NewData->FieldImgName, L"Leene_Center.png");

	lstrcpyW(NewData->ColImgName, L"Leene_Center_Col.png");

	NewData->FieldAnimationSize = 3;

	Vector = NTVEC{ 767.0f * 4.0f, 755.0f * 4.0f };
	memcpy_s(NewData->MapSize, sizeof(float) * 4, &Vector, sizeof(float) * 4);

	lstrcpyW(NewData->FieldAnimation[0].Key, L"StandFlag01");
	lstrcpyW(NewData->FieldAnimation[0].SourceImgName, L"Leene_Obj.png");
	lstrcpyW(NewData->FieldAnimation[0].AnimationName, L"StandFlag");
	NewData->FieldAnimation[0].StartFrame = 0;
	NewData->FieldAnimation[0].Endframe = 2;
	NewData->FieldAnimation[0].FrameSpeed = 0.1f;
	NewData->FieldAnimation[0].Loop = true;
	Vector = NTVEC{ -210.0f, 254.0f, -1.0f };
	memcpy_s(NewData->FieldAnimation[0].Pivot, sizeof(float) * 4, &Vector, sizeof(float) * 4);
	Vector = NTVEC{ 400.0f, 400.0f, 1.0f };
	memcpy_s(NewData->FieldAnimation[0].Scale, sizeof(float) * 4, &Vector, sizeof(float) * 4);

	lstrcpyW(NewData->FieldAnimation[1].Key, L"SmallFlag01");
	lstrcpyW(NewData->FieldAnimation[1].SourceImgName, L"Leene_Obj.png");
	lstrcpyW(NewData->FieldAnimation[1].AnimationName, L"SmallFlag1");
	NewData->FieldAnimation[1].StartFrame = 7;
	NewData->FieldAnimation[1].Endframe = 9;
	NewData->FieldAnimation[1].FrameSpeed = 0.1f;
	NewData->FieldAnimation[1].Loop = true;
	Vector = NTVEC{ -270.0f, -190.0f, -1.0f };
	memcpy_s(NewData->FieldAnimation[1].Pivot, sizeof(float) * 4, &Vector, sizeof(float) * 4);
	Vector = NTVEC{ 400.0f, 400.0f, 1.0f };
	memcpy_s(NewData->FieldAnimation[1].Scale, sizeof(float) * 4, &Vector, sizeof(float) * 4);

	lstrcpyW(NewData->FieldAnimation[2].Key, L"Fountain");
	lstrcpyW(NewData->FieldAnimation[2].SourceImgName, L"Leene_Obj.png");
	lstrcpyW(NewData->FieldAnimation[2].AnimationName, L"Fountain");
	NewData->FieldAnimation[2].StartFrame = 3;
	NewData->FieldAnimation[2].Endframe = 5;
	NewData->FieldAnimation[2].FrameSpeed = 0.1f;
	NewData->FieldAnimation[2].Loop = true;
	Vector = NTVEC{ 0.0f, -590.0f, -1.0f };
	memcpy_s(NewData->FieldAnimation[2].Pivot, sizeof(float) * 4, &Vector, sizeof(float) * 4);
	Vector = NTVEC{ 400.0f, 400.0f, 1.0f };
	memcpy_s(NewData->FieldAnimation[2].Scale, sizeof(float) * 4, &Vector, sizeof(float) * 4);


	lstrcpyW(NewData->Key, L"Leene_Center");
	Vector = NTVEC{ 510.0f, -440.0f, 5.0f, 0.0f };
	NewData->FieldNPCSize = 1;
	NewData->FieldNPC[0].RenderType = (int)NTNPC::NPCRENDERTYPE::NRT_AD_GREENGUY; 
	NewData->FieldNPC[0].EventType = (int)NTNPC::NPCEVENTTYPE::NET_CONVERSATION;
	NewData->FieldNPC[0].TextListSize = 1;
	NewData->FieldNPC[0].TextStart[0] = 0;
	NewData->FieldNPC[0].TextSize[0] = 2;
	NewData->FieldNPC[0].TextNumArr[0][0] = 0;
	NewData->FieldNPC[0].TextNumArr[0][1] = 1;
	NewData->FieldNPC[0].bBattle = false;
	memcpy_s(NewData->FieldNPC[0].Pos, sizeof(float) * 4, &Vector, sizeof(float) * 4);
	lstrcpyW(NewData->FieldNPC[0].Name, L"잉여");

	TempKey = NewData->Key;
	FieldMap.insert(std::unordered_map<std::wstring, FieldData>::value_type(TempKey, *NewData));

	delete NewData;
	NewData = nullptr;
#pragma endregion
	
#pragma region Leene_Right Init
	NewData = new FieldData();
	lstrcpyW(NewData->FieldImgName, L"Leene_Right.png");
	lstrcpyW(NewData->ColImgName, L"Leene_Right_Col.png");

	NewData->FieldAnimationSize = 0;

	Vector = NTVEC{ 256.0f * 4.0f, 243.0f * 4.0f };
	memcpy_s(NewData->MapSize, sizeof(NTVEC), &Vector, sizeof(NTVEC));

	lstrcpyW(NewData->Key, L"Leene_Right");
	TempKey = NewData->Key;
	FieldMap.insert(std::unordered_map<std::wstring, FieldData>::value_type(TempKey, *NewData));
	delete NewData;
	NewData = nullptr;
#pragma endregion

#pragma region Leene_Left Init
	NewData = new FieldData();
	lstrcpyW(NewData->FieldImgName, L"Leene_Left.png");
	lstrcpyW(NewData->ColImgName, L"Leene_Left_Col.png");

	NewData->FieldAnimationSize = 0;

	Vector = NTVEC{ 256.0f * 4.0f, 243.0f * 4.0f };
	memcpy_s(NewData->MapSize, sizeof(NTVEC), &Vector, sizeof(NTVEC));


	
	Vector = NTVEC{ 0.0f, 0.0f, 5.0f, 0.0f };
	memcpy_s(NewData->FieldNPC[0].Pos, sizeof(float) * 4, &Vector, sizeof(float) * 4);
	NewData->FieldNPCSize = 1;
	NewData->FieldNPC[0].RenderType = (int)NTNPC::NPCRENDERTYPE::NRT_AD_GONZALEZ;
	NewData->FieldNPC[0].EventType = (int)NTNPC::NPCEVENTTYPE::NET_CONVBATLLE;
	NewData->FieldNPC[0].TextListSize = 2;
	NewData->FieldNPC[0].TextStart[0] = 2;
	NewData->FieldNPC[0].TextSize[0] = 1;
	NewData->FieldNPC[0].TextNumArr[0][0] = 2;
	NewData->FieldNPC[0].TextStart[1] = 3;
	NewData->FieldNPC[0].TextSize[1] = 1;
	NewData->FieldNPC[0].TextNumArr[1][0] = 3;
	NewData->FieldNPC[0].bBattle = true;
	lstrcpyW(NewData->FieldNPC[0].Name, L"곤잘레스");

	lstrcpyW(NewData->Key, L"Leene_Left");
	TempKey = NewData->Key;
	FieldMap.insert(std::unordered_map<std::wstring, FieldData>::value_type(TempKey, *NewData));
	delete NewData;
	NewData = nullptr;
#pragma endregion
}

bool NTField::Init()
{
	return true;
}

bool NTField::Init(const wchar_t * _ImageName)
{
	std::wstring TmpName = _ImageName;
	size_t CutCount = TmpName.find_last_of('.', TmpName.size());
	TmpName.replace(CutCount, TmpName.size(), L"_Col.png");
	
	return Init(_ImageName, TmpName.c_str());
}

bool NTField::Init(const wchar_t* _FieldImageName, const wchar_t* _ColImageName)
{
	FieldImage = AddComponent<NTSpRenderer>(_FieldImageName);
	ColImage = AddComponent<NTSpRenderer>(_ColImageName);

	FieldImage->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	ColImage->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	return true;
}

void NTField::SetImageSize(const NTVEC & _Size)
{
	FieldImage->SetSubScale(_Size);
	ColImage->SetSubScale(_Size);

	MapSize.Pos = GetNTObject()->GetTransform()->GetLocalPosition().Pos;
	MapSize.Size = _Size.Pos;
}

Autoptr<NTObject> NTField::CreateFieldObj(const wchar_t* _Key, const wchar_t* _ImgName, const wchar_t * _AniName, size_t _StartFrame, size_t _EndFrame, float _FrameSpeed, bool _Loop)
{
	Autoptr<NTObject> NewObj = GetScene()->CreateObject(_Key, NPCLayer);
	Autoptr<NTSpRenderer> Renderer = NewObj->AddComponent<NTSpRenderer>(_ImgName);
	Autoptr<NTSpFrameAnimator> Animator = NewObj->AddComponent<NTSpFrameAnimator>();
	Animator->SetSpRenderer(Renderer);
	Animator->CreateAnimation(_AniName, _StartFrame, _EndFrame, _FrameSpeed, _Loop);
	Animator->ChangeAnimation(_AniName);
	GetNTObject()->AddChild(NewObj, false);
	FieldObjMap.insert(std::unordered_map<std::wstring, Autoptr<NTObject>>::value_type(_Key, NewObj));
	return NewObj;
}

void NTField::AddFieldObj(Autoptr<NTObject> _Obj)
{
	FieldObjMap.insert(std::unordered_map<std::wstring, Autoptr<NTObject>>::value_type(_Obj->GetName(), _Obj));
}

Autoptr<NTObject> NTField::GetFieldObj(const wchar_t* _Key)
{
	std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator FindIter = FieldObjMap.find(_Key);

	if (FindIter == FieldObjMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void NTField::MainUpdate()
{
	
}

void NTField::ChangeField(const wchar_t * _FieldKey)
{
	GetNTObject()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 100.0f });

	if (FieldImage == nullptr)
	{
		FieldImage = AddComponent<NTSpRenderer>();
	}

	if (ColImage == nullptr)
	{
		ColImage = AddComponent<NTSpRenderer>();
	}

	if (FieldObjMap.size() > 0)
	{
		std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator Startiter = FieldObjMap.begin();
		std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator Enditer = FieldObjMap.end();
		for (; Startiter != Enditer; ++Startiter)
		{
			Startiter->second->Death();
		}
	}

	if (FieldNPCMap.size() > 0)
	{
		std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator Startiter = FieldNPCMap.begin();
		std::unordered_map<std::wstring, Autoptr<NTObject>>::iterator Enditer = FieldNPCMap.end();
		for (; Startiter != Enditer; ++Startiter)
		{
			Startiter->second->Death();
		}
	}

	//std::unordered_map<std::wstring, Autoptr<NTEvent>> FieldEventMap; 얘는 데이터기반으로 불러오는게 아니라
	// 지금은 지워서는 안됨. 그럼 어떻게하지?
	// 잠깐 꺼놓고 다시 켜는식으로 가야하나?

	FieldImage->SetMode(NTSubTransform::SUBMODE::SM_PARENT);
	ColImage->SetMode(NTSubTransform::SUBMODE::SM_PARENT);

	FieldData TmpData = FindFieldData(_FieldKey);

	FieldImage->SetImage(TmpData.FieldImgName);
	ColImage->SetImage(TmpData.ColImgName);

	for (int i = 0; i < TmpData.FieldAnimationSize; i++)
	{
		Autoptr<NTSpFrameAnimator> TmpP = CreateFieldObj(TmpData.FieldAnimation[i].Key, TmpData.FieldAnimation[i].SourceImgName, TmpData.FieldAnimation[i].AnimationName, TmpData.FieldAnimation[i].StartFrame, TmpData.FieldAnimation[i].Endframe, TmpData.FieldAnimation[i].FrameSpeed, TmpData.FieldAnimation[i].Loop)->GetComponent<NTSpFrameAnimator>();
		TmpP->GetSpRenderer()->SetSubPivot(NTVEC{ TmpData.FieldAnimation[i].Pivot[0], TmpData.FieldAnimation[i].Pivot[1],TmpData.FieldAnimation[i].Pivot[2],TmpData.FieldAnimation[i].Pivot[3] });
		TmpP->GetSpRenderer()->SetSubScale(NTVEC{ TmpData.FieldAnimation[i].Scale[0], TmpData.FieldAnimation[i].Scale[1],TmpData.FieldAnimation[i].Scale[2],TmpData.FieldAnimation[i].Scale[3] });
		TmpP->GetSpRenderer()->SetMode(NTSubTransform::SUBMODE::SM_SELF);
	}

	for (int i = 0; i < TmpData.FieldNPCSize; i++)
	{
		NTVEC Pos = 0.0f;
		memcpy_s(&Pos, sizeof(NTVEC), TmpData.FieldNPC[i].Pos, sizeof(NTVEC));
		Autoptr<NTObject> NewNPCObj = GetScene()->CreateObject(TmpData.FieldNPC[i].Name, NPCLayer);
		Autoptr<NTNPC> NewNPC = NewNPCObj->AddComponent<NTNPC>((NTNPC::NPCRENDERTYPE)TmpData.FieldNPC[i].RenderType, (NTNPC::NPCEVENTTYPE)TmpData.FieldNPC[i].EventType);
		for (int j = 0; j < TmpData.FieldNPC[i].TextListSize; j++)
		{
			NewNPC->AddTextList();
			NewNPC->SetStartCount(j, TmpData.FieldNPC[i].TextStart[j]);
			for (int k = 0; k < TmpData.FieldNPC[i].TextSize[j]; k++)
			{
				NewNPC->AddText(j, TmpData.FieldNPC[i].TextNumArr[j][k]);
			}
		}

		if (TmpData.FieldNPC[i].bBattle == true)
		{
			NTEnemy* Tmp = NewNPCObj->AddComponent<NTEnemy>();
			Tmp->SetAnimator(NewNPCObj->GetComponent<NTSpFrameAnimator>());
		}
		NewNPCObj->GetTransform()->SetLocalPosition(Pos);
		AddNPC(NewNPCObj);
	}
	
	SetImageSize(FieldImage->GetImage()->GetTex()->GetImageSize() * 4.0f);

	if (NTWinShortCut::GetMainSceneSystem().GetCurScene() != nullptr)
	{
		NTWinShortCut::GetMainSceneSystem().GetCurScene()->GetMainCamera()->GetNTObject()->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f }); // 아 이거 이동위치에 따른 카메라 강제이동
		NTWinShortCut::GetMainSceneSystem().GetCurScene()->GetMainCamera()->GetNTObject()->GetTransform()->ForceMove();
	}

	ColImage->SetSubPivot({ ColImage->GetSubPivot().Pos,  NTVEC2{ GetScene()->GetMainCamera()->GetNTObject()->GetTransform()->GetLocalPosition().z - 100.0f, 0.0f } });
}

void NTField::CreateNTEvent(const wchar_t * _EventName)
{
	Autoptr<NTEvent> NewEvent = AddComponent<NTEvent>();

	FieldEventMap.insert(std::unordered_map<std::wstring, Autoptr<NTEvent>>::value_type(_EventName, NewEvent));
}

Autoptr<NTEvent> NTField::GetNTEvent(const wchar_t * _EventName)
{
	std::unordered_map<std::wstring, Autoptr<NTEvent>>::iterator FindIter = FieldEventMap.find(_EventName);

	if (FindIter == FieldEventMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}
