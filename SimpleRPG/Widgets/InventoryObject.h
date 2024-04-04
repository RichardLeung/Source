// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleRPG/Datas/ItemData.h"
#include "UObject/NoExportTypes.h"
#include "InventoryObject.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERPG_API UInventoryObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory Object")
	UItemData* ItemData;
	
};
