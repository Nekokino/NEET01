#include "TextLoader.h"

#include "GameSystem.h"
#include <ResourceSystem.h>
#include <NTReadStream.h>
#include <string>



TextLoader::TextLoader()
{
}


TextLoader::~TextLoader()
{
}

void TextLoader::Load()
{
	memset(GameSystem::GetTextData(0), 0, sizeof(wchar_t) * TextMaxIndex * TextMaxBuf);

	std::wstring SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"TextData.neet";

	NTReadStream ReadStream = NTReadStream(SaveData.c_str());

	int Count = 0;
	ReadStream.Read(&Count, sizeof(int), sizeof(int));

	for (int i = 0; i < Count; ++i)
	{
		wchar_t TextData[TextMaxBuf] = {};
		ReadStream.Read(TextData, sizeof(TextData), sizeof(TextData));
		GameSystem::SetText(TextData, i);
	}
}