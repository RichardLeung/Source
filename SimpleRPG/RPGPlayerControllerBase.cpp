// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerControllerBase.h"

#include <functional>

#include "RPGGameInstanceBase.h"
#include "RPGSaveGame.h"
#include "RPGTypes.h"
#include "Datas/ItemData.h"
#include "Datas/WeaponBaseModel.h"
#include "Blueprint/UserWidget.h"
#include "Characters/RPGCharacterBase.h"
#include "Widgets/GameHUD.h"

// 初始化静态成员变量
int32 ARPGPlayerControllerBase::WeaponNextId = 0;

ARPGPlayerControllerBase::ARPGPlayerControllerBase()
{
	WeaponNextId = 0;
}

void ARPGPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

bool ARPGPlayerControllerBase::GetInventoryItemData(UItemData* Item, FRPGItemData& ItemData) const
{
	const FRPGItemData* FoundItem = InventoryData.Find(Item);

	if (FoundItem)
	{
		ItemData = *FoundItem;
		return true;
	}
	ItemData = FRPGItemData(0, 0);
	return false;
}

bool ARPGPlayerControllerBase::AddInventoryItem(UItemData* NewItem, int32 ItemCount, int32 ItemLevel)
{
	UE_LOG(LogTemp, Warning, TEXT("添加道具开始"));
	if (NewItem->ItemType == EItemType::Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("添加武器"));
		// 从GameInstance中获取武器数据
		URPGGameInstanceBase* GameInstance = Cast<URPGGameInstanceBase>(GetGameInstance());
		FWeaponBaseModel* WeaponBaseModel = GameInstance->WeaponData.Find(FName(*NewItem->ItemName.ToString()));
		// 生成武器模型
		UWeaponModel* WeaponModel = NewObject<UWeaponModel>();
		// 设置武器模型的属性
		WeaponModel->Id = WeaponNextId;
		WeaponModel->Level = 1;
		WeaponModel->EquippedCharacter = FName("None");
		WeaponModel->BaseInfo = *WeaponBaseModel;
		// 添加到武器列表
		Weapons.Add(WeaponNextId, WeaponModel);
		WeaponNextId++;
		UE_LOG(LogTemp, Warning, TEXT("添加武器完成"));
		UE_LOG(LogTemp, Warning, TEXT("武器ID：%d"), WeaponModel->Id);
		UE_LOG(LogTemp, Warning, TEXT("武器等级：%d"), WeaponModel->Level);
		UE_LOG(LogTemp, Warning, TEXT("武器名称：%s"), *WeaponModel->BaseInfo.Name.ToString());
		return true;
	}
	// bool bChanged = false;
	// if (!NewItem)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("AddInventoryItem: Failed trying to add null item!"));
	// 	return false;
	// }
	//
	// if (ItemCount <= 0)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("AddInventoryItem: Failed trying to add item %s with negative count or level!"), *NewItem->GetName());
	// 	return false;
	// }
	//
	// // Find current item data, which may be empty
	// FRPGItemData OldData;
	// GetInventoryItemData(NewItem, OldData);
	//
	// // Find modified data
	// FRPGItemData NewData = OldData;
	// NewData.UpdateItemData(FRPGItemData(ItemCount, ItemLevel), NewItem->MaxStackSize, 1);
	//
	// if (OldData != NewData)
	// {
	// 	// If data changed, need to update storage and call callback
	// 	InventoryData.Add(NewItem, NewData);
	// 	NotifyInventoryItemChanged(true, NewItem);
	// 	bChanged = true;
	// }
	// UE_LOG(LogTemp, Warning, TEXT("所有道具种类数：%d"),InventoryData.Num());
	// UE_LOG(LogTemp, Warning, TEXT("这个道具的个数：%d"), NewData.ItemCount);
	// UE_LOG(LogTemp, Warning, TEXT("添加道具完成"));
	// if (bChanged)
	// {
	// 	// If anything changed, write to save game
	// 	SaveInventory();
	// 	ARPGCharacterBase* PlayerCharacter = Cast<ARPGCharacterBase>(GetCharacter());
	// 	PlayerCharacter->OnInventoryItemsChanged();
	// 	return true;
	// }
	return false;
}

bool ARPGPlayerControllerBase::RemoveInventoryItem(UItemData* RemovedItem, int32 RemoveCount)
{
	if (!RemovedItem)
	{
		UE_LOG(LogTemp, Warning, TEXT("RemoveInventoryItem: Failed trying to remove null item!"));
		return false;
	}

	// Find current item data, which may be empty
	// 找到当前的物品数据，它可能是空的
	FRPGItemData OldData;
	GetInventoryItemData(RemovedItem, OldData);

	// Find modified data
	// 找到修改的数据
	FRPGItemData NewData = OldData;
	NewData.UpdateItemData(FRPGItemData(-RemoveCount, 0), RemovedItem->MaxStackSize, 1);

	if (OldData != NewData)
	{
		// If data changed, need to update storage and call callback
		// 如果数据发生了变化，需要更新存储并调用回调
		InventoryData.Add(RemovedItem, NewData);
		NotifyInventoryItemChanged(false, RemovedItem);
		SaveInventory();
		return true;
	}
	return false;
}

void ARPGPlayerControllerBase::GetInventoryItems(TArray<UItemData*>& Items, FPrimaryAssetType ItemType)
{
	for (const TPair<UItemData*, FRPGItemData>& Pair : InventoryData)
	{
		if (Pair.Key)
		{
			FPrimaryAssetId AssetId = Pair.Key->GetPrimaryAssetId();

			// Filters based on item type
			if (AssetId.PrimaryAssetType == ItemType || !ItemType.IsValid())
			{
				Items.Add(Pair.Key);
			}
		}
	}
}

bool ARPGPlayerControllerBase::SaveInventory()
{
	UWorld* World = GetWorld();
	URPGGameInstanceBase* GameInstance = World ? World->GetGameInstance<URPGGameInstanceBase>() : nullptr;

	URPGSaveGame* CurrentSaveGame = GameInstance->GetCurrentSaveGame();
	if (CurrentSaveGame)
	{
		// Reset cached data in save game before writing to it
		CurrentSaveGame->InventoryData.Reset();

		for (const TPair<UItemData*, FRPGItemData>& ItemPair : InventoryData)
		{
			FPrimaryAssetId PrimaryAssetId;
			if (ItemPair.Key)
			{
				PrimaryAssetId = ItemPair.Key->GetPrimaryAssetId();
				CurrentSaveGame->InventoryData.Add(PrimaryAssetId, ItemPair.Value);
			}
		}
		return GameInstance->WriteSaveGame();
	}
	return false;
}

void ARPGPlayerControllerBase::NotifyInventoryLoaded()
{
	// Notify native before blueprint
	// 在蓝图之前通知本机
	OnInventoryLoadedNative.Broadcast();
	OnInventoryLoaded.Broadcast();
}

bool ARPGPlayerControllerBase::LoadInventory()
{
	InventoryData.Reset();

	// Fill in slots from game instance
	// 从游戏实例中填充插槽
	UWorld* World = GetWorld();
	URPGGameInstanceBase* GameInstance = World ? World->GetGameInstance<URPGGameInstanceBase>() : nullptr;
	if (!GameInstance)
	{
		return false;
	}
	// Bind to loaded callback if not already bound
	// 如果尚未绑定，请绑定到已加载的回调
	if (!GameInstance->OnSaveGameLoaded.IsAlreadyBound(this, &ARPGPlayerControllerBase::HandleSaveGameLoaded))
	{
		GameInstance->OnSaveGameLoaded.AddDynamic(this, &ARPGPlayerControllerBase::HandleSaveGameLoaded);
	}

	URPGSaveGame* CurrentSaveGame = GameInstance->GetCurrentSaveGame();
	URPGAssetManager& AssetManager = URPGAssetManager::Get();
	if (CurrentSaveGame)
	{
		// Copy from save game into controller data
		// 从保存游戏复制到控制器数据
		for (const TPair<FPrimaryAssetId, FRPGItemData>& ItemPair : CurrentSaveGame->InventoryData)
		{
			UItemData* Item = AssetManager.ForceLoadItem(ItemPair.Key);
			if (Item)
			{
				InventoryData.Add(Item, ItemPair.Value);
			}
		}
		NotifyInventoryLoaded();
		return true;
	}
	// Load failed but we reset inventory, so need to notify UI
	// 加载失败，但我们重置了库存，因此需要通知UI
	NotifyInventoryLoaded();
	return false;
}

void ARPGPlayerControllerBase::NotifyInventoryItemChanged(bool bAdded, UItemData* Item)
{
	// Notify native before blueprint
	OnInventoryItemChangedNative.Broadcast(bAdded, Item);
	OnInventoryItemChanged.Broadcast(bAdded, Item);

	// Call BP update event
	InventoryItemChanged(bAdded, Item);
}

void ARPGPlayerControllerBase::HandleSaveGameLoaded(URPGSaveGame* NewSaveGame)
{
	LoadInventory();
}
