#pragma once

#include "CoreMinimal.h"
#include "WeaponBaseModel.generated.h"

USTRUCT(BlueprintType)
struct FWeaponBaseModel: public FTableRowBase
{
	GENERATED_BODY()

	// 武器名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName Name;
	
	// 武器描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FText Description;

	// 武器图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	UTexture2D* Icon;
	
	// 武器品质
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	int32 Quality;

	// 武器详情的软引用
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSoftObjectPtr<UDataAsset> WeaponData;
};



