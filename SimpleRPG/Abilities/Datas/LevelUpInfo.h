// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FRPGLevelUpInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpRequirement = 0;

	// 属性
	UPROPERTY(EditDefaultsOnly)
	int32 HPBase = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 DMG = 0;
};

/**
 * 
 */
UCLASS()
class SIMPLERPG_API ULevelUpInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FRPGLevelUpInfo> LevelUpInformation;

	int32 FindLevelForXP(int32 XP);
};
