// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGTypes.h"
#include "GameFramework/SaveGame.h"
#include "RPGSaveGame.generated.h"

/** List of versions, native code will handle fixups for any old versions */
namespace ERPGSaveGameVersion
{
	enum type
	{
		// Initial version
		// 初始化版本
		Initial,
		// Added Inventory
		// 添加道具
		AddedInventory,
		// Added ItemData to store count/level
		// 添加道具数据，用于存储数量/等级
		AddedItemData,

		// -----<new versions must be added before this line>-------------------------------------------------
		// -----<新版本必须在此行之前添加>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};
}

/**
 * 
 */
UCLASS()
class SIMPLERPG_API URPGSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/** Constructor */
	// 构造函数
	URPGSaveGame()
	{
		// Set to current version, this will get overwritten during serialization when loading
		// 设置为当前版本，当加载时，此版本将在序列化期间被覆盖
		SavedDataVersion = ERPGSaveGameVersion::LatestVersion;
	}

	/** Map of items to item data */
	// 道具到道具数据的映射
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
	TMap<FPrimaryAssetId, FRPGItemData> InventoryData;

	/** User's unique id */
	// 用户的唯一ID
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
	FString UserId;

protected:
	/** Deprecated way of storing items, this is read in but not saved out */
	// 存储道具的过时方法，这是读取的，但没有保存
	UPROPERTY()
	TArray<FPrimaryAssetId> InventoryItems_DEPRECATED;

	/** What LatestVersion was when the archive was saved */
	// 存档保存时的最新版本
	UPROPERTY()
	int32 SavedDataVersion;

	/** Overridden to allow version fixups */
	// 重写以允许版本修复
	virtual void Serialize(FArchive& Ar) override;
};
