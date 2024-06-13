// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelUpInfo.generated.h"

USTRUCT(BlueprintType)
struct FRPGLevelUpAttribute
{
	GENERATED_BODY()

	// 生命值
	UPROPERTY(EditDefaultsOnly)
	int32 HPBase = 0;

	// 攻击
	UPROPERTY(EditDefaultsOnly)
	int32 DMG = 0;

	// 防御
	UPROPERTY(EditDefaultsOnly)
	int32 DEF = 0;

	// 速度
	UPROPERTY(EditDefaultsOnly)
	int32 SPD = 0;

	// 暴击率
	UPROPERTY(EditDefaultsOnly)
	float CritRate = 0;

	// 暴击伤害
	UPROPERTY(EditDefaultsOnly)
	float CritDMG = 0;
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
	TArray<FRPGLevelUpAttribute> AttributesLevelUp;
};
