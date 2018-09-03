#pragma once
#include <NTLogic.h>

#include <vector>

class NTSpRenderer;
class NTPieceWindow : public NTLogic
{
private:
	std::vector<Autoptr<NTSpRenderer>> RendererVector;
public:
	bool Init(size_t _Row, size_t _Col, float _Size = 1.0f);
	void MainUpdate() override;
	void DbgRender() override;

	void HideWindow();
	void ShowWindow();
public:
	NTPieceWindow();
	~NTPieceWindow();
};

