// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBaseModel.h"
#include "UObject/Object.h"
#include "WeaponModel.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SIMPLERPG_API UWeaponModel : public UObject
{
	GENERATED_BODY()

public:
	// 唯一ID，自增ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Id;

	// 武器等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Level;

	// 武器当前装备的角色
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName EquippedCharacter;

	// 武器基本信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FWeaponBaseModel BaseInfo;
};
