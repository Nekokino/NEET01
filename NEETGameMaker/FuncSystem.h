#pragma once

#include <functional>
#include <unordered_map>
#include <string>

class FuncSystem
{
private:
	static std::unordered_map<std::wstring, std::function<void()>> VoidFuncMap;

public:
	static void InitSystem();

	static void CallVoidFunc(const wchar_t* _FuncName);
public:
	FuncSystem();
	virtual ~FuncSystem() = 0;
};

