#include "ItemLoader.h"

#include <string>
#include <ResourceSystem.h>
#include <NTReadStream.h>
#include "NTItemData.h"
#include "NTWeapon.h"
#include "NTArmor.h"
#include "NTHelmet.h"
#include "NTAcc.h"
#include "NTConsume.h"
#include "NTKeyItem.h"


ItemLoader::ItemLoader()
{
}


ItemLoader::~ItemLoader()
{
}

void ItemLoader::Load()
{
	NTItem::ItemData;

	std::wstring SaveData = PathSystem::FindPath(L"Data");
	SaveData += L"ItemData.neet";

	NTReadStream ReadStream = NTReadStream(SaveData.c_str());

	int Count = 0;
	ReadStream.Read(&Count, sizeof(int), sizeof(int));

	for (int i = 0; i < Count; ++i)
	{
		char TypeNameBuf[20];
		ReadStream.Read(TypeNameBuf, sizeof(TypeNameBuf), sizeof(TypeNameBuf));
		NTItemData* NewItem = new NTItemData();
		ReadStream.Read(NewItem, sizeof(NTItemData), sizeof(NTItemData));

		if (strcmp(TypeNameBuf, "class NTWeapon") == 0)
		{
			NTWeapon* NewWeapon = new NTWeapon();
			NewWeapon->Atk = NewItem->Stat;
			NewWeapon->bSpecial = NewItem->bSpecial;
			NewWeapon->Crit = NewItem->Crit;
			NewWeapon->SetName(NewItem->Name);
			NewWeapon->Info = NewItem->Info;
			memcpy_s(NewWeapon->Only, sizeof(NewWeapon->Only), NewItem->Only, sizeof(NewItem->Only));
			NewWeapon->Output = NewItem->Output;
			NewWeapon->Price = NewItem->Price;
			NewWeapon->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NewWeapon->WeaponType = (NTWeapon::WEAPONTYPE)NewItem->Type;
			NTItem::ItemData.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(NewWeapon->GetName(), NewWeapon));
		}

		if (strcmp(TypeNameBuf, "class NTArmor") == 0)
		{
			NTArmor* NewArmor = new NTArmor();
			NewArmor->Def = NewItem->Stat;
			NewArmor->bSpecial = NewItem->bSpecial;
			NewArmor->SetName(NewItem->Name);
			NewArmor->Info = NewItem->Info;
			memcpy_s(NewArmor->Only, sizeof(NewArmor->Only), NewItem->Only, sizeof(NewItem->Only));
			NewArmor->Output = NewItem->Output;
			NewArmor->Price = NewItem->Price;
			NewArmor->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NTItem::ItemData.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(NewArmor->GetName(), NewArmor));
		}

		if (strcmp(TypeNameBuf, "class NTHelmet") == 0)
		{
			NTHelmet* NewHelmet = new NTHelmet();
			NewHelmet->Def = NewItem->Stat;
			NewHelmet->bSpecial = NewItem->bSpecial;
			NewHelmet->SetName(NewItem->Name);
			NewHelmet->Info = NewItem->Info;
			memcpy_s(NewHelmet->Only, sizeof(NewHelmet->Only), NewItem->Only, sizeof(NewItem->Only));
			NewHelmet->Output = NewItem->Output;
			NewHelmet->Price = NewItem->Price;
			NewHelmet->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NTItem::ItemData.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(NewHelmet->GetName(), NewHelmet));
		}

		if (strcmp(TypeNameBuf, "class NTAcc") == 0)
		{
			NTAcc* NewAcc = new NTAcc();
			NewAcc->bSpecial = NewItem->bSpecial;
			NewAcc->SetName(NewItem->Name);
			NewAcc->Info = NewItem->Info;
			memcpy_s(NewAcc->Only, sizeof(NewAcc->Only), NewItem->Only, sizeof(NewItem->Only));
			NewAcc->Output = NewItem->Output;
			NewAcc->Price = NewItem->Price;
			NewAcc->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc
			NTItem::ItemData.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(NewAcc->GetName(), NewAcc));
		}

		if (strcmp(TypeNameBuf, "class NTConsume") == 0)
		{
			NTConsume* NewConsume = new NTConsume();
			NewConsume->SetName(NewItem->Name);
			NewConsume->Info = NewItem->Info;
			NewConsume->Output = NewItem->Output;
			NewConsume->Price = NewItem->Price;
			NewConsume->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NTItem::ItemData.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(NewConsume->GetName(), NewConsume));
		}

		if (strcmp(TypeNameBuf, "class NTKeyItem") == 0)
		{
			NTKeyItem* NewKeyItem = new NTKeyItem();
			NewKeyItem->SetName(NewItem->Name);
			NewKeyItem->Info = NewItem->Info;
			NewKeyItem->Output = NewItem->Output;
			NewKeyItem->Price = NewItem->Price;
			NewKeyItem->Sellable = NewItem->Sellable;
			//NewWeapon->SpecialFunc 
			NTItem::ItemData.insert(std::unordered_map<std::wstring, Autoptr<NTItem>>::value_type(NewKeyItem->GetName(), NewKeyItem));
		}

		delete NewItem;
	}
}