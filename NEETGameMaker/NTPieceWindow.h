#pragma once
#include <NTLogic.h>
class NTPieceWindow : public NTLogic
{
public:
	bool Init(size_t _Row, size_t _Col, float _Size = 1.0f);
	void MainUpdate() override;
	void DbgRender() override;
public:
	NTPieceWindow();
	~NTPieceWindow();
};

