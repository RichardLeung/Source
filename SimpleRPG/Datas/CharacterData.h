#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterData.generated.h"

USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
{
	GENERATED_BODY()

	// 角色名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础信息")
	FText Name;

	// 角色描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础信息")
	FText Description;

	// 角色头像
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础信息")
	UTexture2D* Avatar;

	// 角色各个等级的属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|详细信息")
	TSoftObjectPtr<UDataAsset> DA_LevelUpAttributeSet;

	// 角色详情的软引用
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|详细信息")
	TSoftObjectPtr<UDataAsset> DA_CharacterDetail;
};
