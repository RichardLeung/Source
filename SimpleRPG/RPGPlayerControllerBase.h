// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGInventoryInterface.h"
#include "RPGTypes.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerControllerBase.generated.h"

class UItemData;
class UGameHUD;

/**
 * 
 */
UCLASS()
class SIMPLERPG_API ARPGPlayerControllerBase : public APlayerController, public IRPGInventoryInterface
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	ARPGPlayerControllerBase();
	
	virtual void BeginPlay() override;
	
	// Reference to the BP_CounterUI class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameHUDClass;

	// Pointer to the created Counter UI instance
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UGameHUD* GameHUD;
	
	/** Map of all items owned by this player, from definition to data */
	// 由此玩家拥有的所有道具的映射，从定义到数据
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	TMap<UItemData*, FRPGItemData> InventoryData;

	/** Delegate called when an inventory item has been added or removed */
	// 当一个道具被添加或移除时调用的委托
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryItemChanged OnInventoryItemChanged;

	/** Called after the inventory was changed and we notified all delegates */
	// 在库存发生变化并通知所有委托后调用
	/** 提供给蓝图实现 **/
	UFUNCTION(BlueprintImplementableEvent, Category = Inventory)
	void InventoryItemChanged(bool bAdded, UItemData* Item);

	/** Native version above, called before BP delegate */
	// 上面的本机版本，在BP委托之前调用
	FOnInventoryItemChangedNative OnInventoryItemChangedNative;

	/** Delegate called when the inventory has been loaded/reloaded */
	// 当库存已加载/重新加载时调用的委托
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnInventoryLoaded OnInventoryLoaded;

	/** Native version above, called before BP delegate */
	// 上面的本机版本，在BP委托之前调用
	FOnInventoryLoadedNative OnInventoryLoadedNative;

	/** Returns the item data associated with an item. Returns false if none found */
	// 返回与项目相关联的项目数据。如果没有找到，则返回false
	UFUNCTION(BlueprintPure, Category = Inventory)
	bool GetInventoryItemData(UItemData* Item, FRPGItemData& ItemData) const;

	/** Adds a new inventory item, will add it to an empty slot if possible. If the item supports count you can add more than one count. It will also update the level when adding if required */
	// 添加一个新的库存项目，如果可能的话，将其添加到一个空槽中。如果项目支持计数，则可以添加多个计数。如果需要，还将在添加时更新级别
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool AddInventoryItem(UItemData* NewItem, int32 ItemCount = 1, int32 ItemLevel = 1);

	/** Remove an inventory item, will also remove from slots. A remove count of <= 0 means to remove all copies */
	// 删除库存项目，也将从槽中删除。移除计数<= 0意味着删除所有副本
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool RemoveInventoryItem(UItemData* RemovedItem, int32 RemoveCount = 1);

	/** Returns all inventory items of a given type. If none is passed as type it will return all */
	// 返回给定类型的所有库存项目。如果没有传递类型，则将返回所有
	UFUNCTION(BlueprintCallable, Category = Inventory)
	void GetInventoryItems(TArray<UItemData*>& Items, FPrimaryAssetType ItemType);

	/** Manually save the inventory, this is called from add/remove functions automatically */
	// 手动保存库存，这是从add / remove函数自动调用的
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool SaveInventory();

	void NotifyInventoryLoaded();
	/** Loads inventory from save game on game instance, this will replace arrays */
	// 从游戏实例上的保存游戏加载库存，这将替换数组
	UFUNCTION(BlueprintCallable, Category = Inventory)
	bool LoadInventory();

	/** Returns the map of items to data */
	// 返回项目到数据的映射
	virtual const TMap<UItemData*, FRPGItemData>& GetInventoryDataMap() const override
	{
		return InventoryData;
	}

	/** Gets the delegate for inventory item changes */
	// 获取库存项目更改的委托
	virtual FOnInventoryItemChangedNative& GetInventoryItemChangedDelegate() override
	{
		return OnInventoryItemChangedNative;
	}

	/** Gets the delegate for when the inventory loads */
	// 获取库存加载时的委托
	virtual FOnInventoryLoadedNative& GetInventoryLoadedDelegate() override
	{
		return OnInventoryLoadedNative;
	}

protected:
	/** Calls the inventory update callbacks */
	// 调用库存更新回调
	void NotifyInventoryItemChanged(bool bAdded, UItemData* Item);

	/** Called when a global save game as been loaded */
	// 当全局保存游戏已加载时调用
	void HandleSaveGameLoaded(URPGSaveGame* NewSaveGame);
};
