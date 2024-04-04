// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGSaveGame.h"
#include "RPGGameInstanceBase.h"

void URPGSaveGame::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar);

	if (Ar.IsLoading() && SavedDataVersion != ERPGSaveGameVersion::LatestVersion)
	{
		if (SavedDataVersion < ERPGSaveGameVersion::AddedItemData)
		{
			// Convert from list to item data map
			// 从列表转换为道具数据映射
			for (const FPrimaryAssetId& ItemId : InventoryItems_DEPRECATED)
			{
				InventoryData.Add(ItemId, FRPGItemData(1, 1));
			}
	
			InventoryItems_DEPRECATED.Empty();
		}
		
		SavedDataVersion = ERPGSaveGameVersion::LatestVersion;
	}
}
