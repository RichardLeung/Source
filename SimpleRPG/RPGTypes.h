// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/PrimaryAssetId.h"
#include "RPGTypes.generated.h"

class UItemData;
class URPGSaveGame;


USTRUCT(BlueprintType)
struct SIMPLERPG_API FRPGItemData
{
	GENERATED_BODY()

	/** Constructor, default to count/level 1 so declaring them in blueprints gives you the expected behavior */
	FRPGItemData()
		: ItemCount(1)
		, ItemLevel(1)
	{}

	FRPGItemData(int32 InItemCount, int32 InItemLevel)
		: ItemCount(InItemCount)
		, ItemLevel(InItemLevel)
	{}

	/** The number of instances of this item in the inventory, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemCount;

	/** The level of this item. This level is shared for all instances, can never be below 1 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item)
	int32 ItemLevel;

	/** Equality operators */
	bool operator==(const FRPGItemData& Other) const
	{
		return ItemCount == Other.ItemCount && ItemLevel == Other.ItemLevel;
	}
	bool operator!=(const FRPGItemData& Other) const
	{
		return !(*this == Other);
	}

	/** Returns true if count is greater than 0 */
	bool IsValid() const
	{
		return ItemCount > 0;
	}

	/** Append an item data, this adds the count and overrides everything else */
	void UpdateItemData(const FRPGItemData& Other, int32 MaxCount, int32 MaxLevel)
	{
		if (MaxCount <= 0)
		{
			MaxCount = MAX_int32;
		}

		if (MaxLevel <= 0)
		{
			MaxLevel = MAX_int32;
		}

		ItemCount = FMath::Clamp(ItemCount + Other.ItemCount, 1, MaxCount);
		ItemLevel = FMath::Clamp(Other.ItemLevel, 1, MaxLevel);
	}
};

/** Delegate called when an inventory item changes */
//当背包物品改变时调用的委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChanged, bool, bAdded, UItemData*, Item);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemChangedNative, bool, UItemData*);

/** Delegate called when the save game has been loaded/reset */
//当存档被加载或重置时调用的委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoaded, URPGSaveGame*, SaveGame);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedNative, URPGSaveGame*);

/** Delegate called when the entire inventory has been loaded, all items may have been replaced */
//当整个背包被加载时调用的委托，所有物品都可能被替换
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryLoaded);
DECLARE_MULTICAST_DELEGATE(FOnInventoryLoadedNative);
