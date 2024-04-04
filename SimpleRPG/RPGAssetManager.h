// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RPGAssetManager.generated.h"

class UItemData;

/**
 * 
 */
UCLASS()
class SIMPLERPG_API URPGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Constructor and overrides
	URPGAssetManager() {}

	virtual void StartInitialLoading() override;
	
	/** Returns the current AssetManager object */
	static URPGAssetManager& Get();

	/**
	 * Synchronously loads an RPGItem subclass, this can hitch but is useful when you cannot wait for an async load
	 * This does not maintain a reference to the item so it will garbage collect if not loaded some other way
	 *
	 * @param PrimaryAssetId The asset identifier to load
	 * @param bDisplayWarning If true, this will log a warning if the item failed to load
	 */
	UItemData* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
