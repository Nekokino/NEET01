#pragma once

#include <NTLogic.h>
#include <NTSpFrameAnimator.h>
#include <vector>
#include <unordered_map>
#include <string>

class AnimationData
{
public:
	wchar_t Key[128];
	wchar_t SourceImgName[128];
	wchar_t AnimationName[128];
	int StartFrame;
	int Endframe;
	float FrameSpeed;
	bool Loop;
	float Pivot[3];
	float Scale[3];
};

class FieldObjData
{

};

class FieldNPCData
{
public:
	int RenderType;
	int EventType;
	int TextListSize;
	int TextStart[5];
	int TextSize[5];
	int TextNumArr[5][10];
	wchar_t Name[16];
	bool bBattle;
	float Pos[4];
};

class FieldData
{
public:
	wchar_t Key[128];
	wchar_t FieldImgName[128];
	wchar_t ColImgName[128];
	int FieldAnimationSize;
	AnimationData FieldAnimation[30];
	int FieldObjectSize;
	FieldObjData FieldObject[30];
	int FieldNPCSize;
	FieldNPCData FieldNPC[30];
	float MapSize[4];
};


class NTSpRenderer;
class NTEvent;
class NTField : public NTLogic
{
public:
	friend class LoadingSceneBuilder;
public:
	Autoptr<NTSpRenderer> FieldImage;
	Autoptr<NTSpRenderer> ColImage;
	std::unordered_map<std::wstring, Autoptr<NTObject>> FieldObjMap;
	std::unordered_map<std::wstring, Autoptr<NTEvent>> FieldEventMap;
	std::unordered_map<std::wstring, Autoptr<NTObject>> FieldNPCMap;
	NTRECT MapSize;

	// 있어야 할 기능
	// 맵 만들기 (어떤 이미지와 충돌이미지로 셋팅 해줄 것인가)
	// 맵 바꾸기
	// 잘 모루겠다
private:
	static std::unordered_map<std::wstring, FieldData> FieldMap;
	static FieldData FindFieldData(const wchar_t* _Key);
	static void DefaultDataSet();

public:
	bool Init();
	bool Init(const wchar_t* _ImageName);
	bool Init(const wchar_t* _FieldImageName, const wchar_t* _ColImage);

	void SetImageSize(const NTVEC& _Size);
	Autoptr<NTObject> CreateFieldObj(const wchar_t* _Key, const wchar_t* _ImgName, const wchar_t* _AniName, size_t _StartFrame, size_t _EndFrame, float _FrameSpeed, bool _Loop);
	void AddFieldObj(Autoptr<NTObject> _Obj);
	Autoptr<NTObject> GetFieldObj(const wchar_t* _Key);

	Autoptr<NTSpRenderer> GetFieldImage()
	{
		return FieldImage;
	}

	Autoptr<NTSpRenderer> GetColImage()
	{
		return ColImage;
	}

	void MainUpdate() override;
	void ChangeField(const wchar_t* _FieldKey);

	void CreateFieldObj(Autoptr<NTObject> _Obj)
	{
		FieldObjMap.insert(std::unordered_map<std::wstring, Autoptr<NTObject>>::value_type(_Obj->GetName(), _Obj));
		GetNTObject()->AddChild(_Obj);
	}

	void CreateNTEvent(const wchar_t* _EventName);
	Autoptr<NTEvent> GetNTEvent(const wchar_t* _EventName);
	void AddNPC(Autoptr<NTObject> _Obj)
	{
		FieldNPCMap.insert(std::unordered_map<std::wstring, Autoptr<NTObject>>::value_type(_Obj->GetName(), _Obj));
		GetNTObject()->AddChild(_Obj);
	}
public:
	NTField();
	~NTField();
};

