// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "WeaponData.generated.h"


UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Blade UMETA(DisplayName = "Blade"),
	Axe UMETA(DisplayName = "Axe"),
};


/**
 * 
 */
UCLASS()
class SIMPLERPG_API UWeaponData : public UItemData
{
	GENERATED_BODY()

public:
	// 武器骨骼模型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMesh* WeaponSkeletalMesh;

	// 武器类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	EWeaponType WeaponType;

	// 武器当前等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 WeaponCurrentLevel;

	// 武器最大等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	int32 WeaponMaxLevel;

	// 力量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Strength;

	// 智力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Intelligence;

	// 耐力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Endurance;

	// 敏捷
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Agility;

	// 武器碰撞体积
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FVector WeaponCollisionScale;

	// 武器碰撞位置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FVector WeaponCollisionLocation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FVector WeaponBoxExtent;

	// 武器盒子起点
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FVector WeaponBoxStart;

	// 武器盒子终点
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Item)
	FVector WeaponBoxEnd;
};
