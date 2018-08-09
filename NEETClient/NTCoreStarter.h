#pragma once
#include <WinCore.h>
#include <RefNAutoptr.h>

class NTCoreStarter : public WinCore::WinCoreBuilder
{
public:
	void Build() override;

public:
	NTCoreStarter();
	~NTCoreStarter();
};

COREBEGIN(NTCoreStarter, L"MainWindow");

