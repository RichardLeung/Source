// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameInstanceBase.h"
#include "RPGAssetManager.h"
#include "RPGSaveGame.h"
#include "Datas/WeaponBaseModel.h"

#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"

URPGGameInstanceBase::URPGGameInstanceBase()
	: SaveSlot(TEXT("SaveGame"))
	  , SaveUserIndex(0)
{
}

void URPGGameInstanceBase::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("准备加载WeaponDataTable"));
	LoadDataTables();
}

void URPGGameInstanceBase::LoadDataTables()
{
	// 加载武器数据表
	DT_Weapons = LoadObject<UDataTable>(nullptr, TEXT("/Game/_Game/DataTables/DT_Weapon_All.DT_Weapon_All"));
	TArray<FName> AllKeys = DT_Weapons->GetRowNames();
	UE_LOG(LogTemp, Warning, TEXT("加载WeaponDataTable,包含武器：%d"), AllKeys.Num());
	TMap<FName, FWeaponBaseModel> WeaponDataNew;
	// 获取UDataTable的RowMap，这是一个包含所有行的TMap，其中键为RowName，值为void指针
	const TMap<FName, uint8*>& DataTableRowMap = DT_Weapons->GetRowMap();
	// 遍历RowMap并将每个行名和数据添加到我们的MyDataMap中
	for (const auto& RowPair : DataTableRowMap)
	{
		const FName& RowName = RowPair.Key;
		const FWeaponBaseModel* RowData = reinterpret_cast<const FWeaponBaseModel*>(RowPair.Value);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RowData->Name.ToString());
		WeaponDataNew.Add(RowName, *RowData);
	}
	WeaponData = WeaponDataNew;

	// 加载角色数据表
	DT_Characters = LoadObject<UDataTable>(nullptr, TEXT("/Game/_Game/DataTables/DT_Character.DT_Character"));
	TArray<FName> AllCharacterKeys = DT_Characters->GetRowNames();
	UE_LOG(LogTemp, Warning, TEXT("加载CharacterDataTable,包含角色：%d"), AllCharacterKeys.Num());
	TMap<FName, FCharacterData> CharacterDataNew;
	// 获取UDataTable的RowMap，这是一个包含所有行的TMap，其中键为RowName，值为void指针
	const TMap<FName, uint8*>& DataTableRowMap2 = DT_Characters->GetRowMap();
	// 遍历RowMap并将每个行名和数据添加到我们的MyDataMap中
	for (const auto& RowPair : DataTableRowMap2)
	{
		const FName& RowName = RowPair.Key;
		const FCharacterData* RowData = reinterpret_cast<const FCharacterData*>(RowPair.Value);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *RowData->Name.ToString());
		CharacterDataNew.Add(RowName, *RowData);
	}
	CharacterData = CharacterDataNew;

	// 加载升级经验数据表
	DT_LevelExp = LoadObject<UDataTable>(nullptr, TEXT("/Game/_Game/DataTables/DT_LevelExp.DT_LevelExp"));
	TArray<FName> AllLevelExpKeys = DT_LevelExp->GetRowNames();
	UE_LOG(LogTemp, Warning, TEXT("加载LevelExpDataTable,包含等级：%d"), AllLevelExpKeys.Num());
}

URPGSaveGame* URPGGameInstanceBase::GetCurrentSaveGame()
{
	return CurrentSaveGame;
}

bool URPGGameInstanceBase::WriteSaveGame()
{
	if (bSavingEnabled)
	{
		if (bCurrentlySaving)
		{
			// Schedule another save to happen after current one finishes. We only queue one save
			// 在当前保存完成后安排另一个保存。我们只排队一个保存
			bPendingSaveRequested = true;
			return true;
		}
		// Indicate that we're currently doing an async save
		// 表明我们正在进行异步保存
		bCurrentlySaving = true;

		UGameplayStatics::AsyncSaveGameToSlot(GetCurrentSaveGame(), SaveSlot, SaveUserIndex,
		                                      FAsyncSaveGameToSlotDelegate::CreateUObject(
			                                      this, &URPGGameInstanceBase::HandleAsyncSave));
	}
	return false;
}

bool URPGGameInstanceBase::LoadGameFromSlot(const FString& SlotName, int32 UserIndex)
{
	URPGSaveGame* LoadedGame = Cast<URPGSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
	if (LoadedGame)
	{
		CurrentSaveGame = LoadedGame;
		OnSaveGameLoaded.Broadcast(LoadedGame);
		OnSaveGameLoadedNative.Broadcast(LoadedGame);
		return true;
	}
	return false;
}

void URPGGameInstanceBase::HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	ensure(bCurrentlySaving);
	bCurrentlySaving = false;

	if (bPendingSaveRequested)
	{
		// Start another save as we got a request while saving
		// 在保存时，我们得到了一个请求，因此开始另一个保存
		bPendingSaveRequested = false;
		WriteSaveGame();
	}
}
