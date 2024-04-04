// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAssetManager.h"
#include "Datas/ItemData.h"

URPGAssetManager& URPGAssetManager::Get()
{
	URPGAssetManager* This = Cast<URPGAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be RPGAssetManager!"));
		return *NewObject<URPGAssetManager>(); // never calls this
	}
}

void URPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// UAbilitySystemGlobals::Get().InitGlobalData();
}

UItemData* URPGAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning)
{	
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UItemData* LoadedItem = Cast<UItemData>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}

	return LoadedItem;
}