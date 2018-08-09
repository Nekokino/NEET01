#pragma once
#include <NTLogic.h>
#include <NTFontRenderer.h>

class NTSecondUVRenderer;
class NTTextWindow : public NTLogic
{
private:
	Autoptr<NTSecondUVRenderer> Renderer;
	Autoptr<NTFontRenderer> FontRenderer;

	float MaxUv;
	float CurUv;

	float Speed;
	bool Open;
	bool Close;
	bool TextSwitch;
public:
	bool Init(int _Order = 0);
	bool Init(const wchar_t* _ImgName, int _Order = 0);
	void MainUpdate() override;
	void DbgRender() override;

	void OpenText();

	void CloseText()
	{
		if (Open == true)
		{
			return;
		}

		Close = true;
	}

	void SetStyle(int _Index);

	void SetString(const wchar_t* _String);
	void SetColor(unsigned __int8 R, unsigned __int8 G, unsigned __int8 B, unsigned __int8 A);
	void SetColor(int _Color);
	void SetFontSize(float _Size);
	void SetFontPos(NTVEC _Pos);
	void SetFontScale(NTVEC _Scale);
	void SetWindowPos(NTVEC _Pos);
	void SetWindowScale(NTVEC _Scale);
	void SetWindowColor(NTCOLOR _Color);
public:
	NTTextWindow();
	~NTTextWindow();
};

