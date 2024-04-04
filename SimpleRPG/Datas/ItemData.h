// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemData.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon UMETA(DisplayName = "Weapon"),
	Consumable UMETA(DisplayName = "Consumable"),
	QuestItem UMETA(DisplayName = "QuestItem")
};

/**
 * 
 */
UCLASS()
class SIMPLERPG_API UItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// 唯一ID，用于在DataTable中查找项目
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemId;

	// 道具名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	// 道具类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	EItemType ItemType;

	// 道具描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemDescription;

	// 物品图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FSlateBrush ItemIcon;

	// 价格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Price;

	// 最大堆叠数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxStackSize;
};
