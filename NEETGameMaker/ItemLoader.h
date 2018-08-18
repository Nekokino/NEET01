#pragma once
class ItemLoader
{
public:
	static void Load();
private:
	ItemLoader();
	virtual ~ItemLoader() = 0;
};

