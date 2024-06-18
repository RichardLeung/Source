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

	// 角色各个等级的基础属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|详细信息")
	TSoftObjectPtr<UDataTable> DT_LevelUpAttributeSet;
};

USTRUCT(BlueprintType)
struct FCharacterLevelAttributeInfo : public FTableRowBase
{
	GENERATED_BODY()

	// 等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	int32 Level;
	
	// 基础生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	float HPBase;

	// 攻击力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	float ATK;

	// 防御力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	float DEF;

	// 突破等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	int32 BreakLevel;
};

USTRUCT(BlueprintType)
struct FLevelExpInfo : public FTableRowBase
{
	GENERATED_BODY()

	// 等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "等级")
	int32 Level;

	// 升级所需经验
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "等级")
	int32 Exp;
};