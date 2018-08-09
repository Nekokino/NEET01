#include "SpriteLoader.h"

#include <string>
#include <ResourceSystem.h>
#include <NTReadStream.h>
#include <NTImage.h>
#include "NTSpriteData.h"

SpriteLoader::SpriteLoader()
{
}


SpriteLoader::~SpriteLoader()
{
}

void SpriteLoader::Load()
{
	std::wstring SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"SpriteEditData.neet";

	NTReadStream ReadStream = NTReadStream(SaveData.c_str());

	int Count = 0;
	ReadStream.Read(&Count, sizeof(int), sizeof(int));

	for (int i = 0; i < Count; ++i)
	{
		NTSpriteData* Data = new NTSpriteData();

		ReadStream.Read(Data, sizeof(NTSpriteData), sizeof(NTSpriteData));
		if (Data->CutX == 1 && Data->CutY == 1)
		{
			ResourceSystem<NTImage>::Load(Data->PathName, Data->FileName);
			delete Data;
			continue;
		}
		ResourceSystem<NTImage>::Load(Data->PathName, Data->FileName, Data->CutX, Data->CutY);
		delete Data;
	}
}