// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGTypes.h"
#include "Engine/GameInstance.h"
#include "Datas/BaseItemData.h"
#include "Datas/CharacterData.h"
#include "RPGGameInstanceBase.generated.h"

class URPGItem;
class URPGSaveGame;
class UDataTable;

/**
 * 
 */
UCLASS()
class SIMPLERPG_API URPGGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

	// Constructor
	URPGGameInstanceBase();

public:

	virtual void Init() override;

	void LoadDataTables();

	UPROPERTY()
	UDataTable* WeaponDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FBaseItemData> WeaponData;

	UPROPERTY()
	UDataTable* CharacterDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FName, FCharacterData> CharacterData;
	
	/** The slot name used for saving */
	// 用于保存的插槽名称
	UPROPERTY(BlueprintReadWrite, Category = Save)
	FString SaveSlot;

	/** The platform-specific user index */
	// 平台特定的用户索引
	UPROPERTY(BlueprintReadWrite, Category = Save)
	int32 SaveUserIndex;

	/** Returns the current save game, so it can be used to initialize state. Changes are not written until WriteSaveGame is called */
	// 返回当前的保存游戏，以便用于初始化状态。更改不会写入，直到WriteSaveGame被调用
	UFUNCTION(BlueprintCallable, Category = Save)
	URPGSaveGame* GetCurrentSaveGame();

	/** Writes the current save game object to disk. The save to disk happens in a background thread*/
	// 将当前的保存游戏对象写入磁盘。磁盘保存发生在后台线程中
	UFUNCTION(BlueprintCallable, Category = Save)
	bool WriteSaveGame();

	/** Delegate called when the save game has been loaded/reset */
	// 保存游戏已加载/重置时调用的委托
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSaveGameLoaded OnSaveGameLoaded;

	/** Native delegate for save game load/reset */
	// 保存游戏加载/重置的本机委托
	FOnSaveGameLoadedNative OnSaveGameLoadedNative;

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	bool LoadGameFromSlot(const FString& SlotName, int32 UserIndex);

protected:
	/** The current save game object */
	// 当前的保存游戏对象
	UPROPERTY()
	URPGSaveGame* CurrentSaveGame;

	/** Rather it will attempt to actually save to disk */
	// 它是否会尝试实际保存到磁盘
	UPROPERTY()
	bool bSavingEnabled;

	/** True if another save was requested during a save */
	// 如果在保存期间请求了另一个保存，则为true
	UPROPERTY()
	bool bPendingSaveRequested;

	/** True if we are in the middle of doing a save */
	// 如果我们正在执行保存，则为true
	UPROPERTY()
	bool bCurrentlySaving;

	/** Called when the async save happens */
	// 异步保存时调用
	virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	
};
