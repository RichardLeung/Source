#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BaseItemData.generated.h"

USTRUCT(BlueprintType)
struct FBaseItemData : public FTableRowBase
{
	GENERATED_BODY()

	// 道具名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Name;

	// 道具描述
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;

	// 道具图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon;

	// 最大堆叠数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxStackSize;
};

