// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ListView.h"
#include "Components/ProgressBar.h"
#include "Components/TileView.h"
#include "GameHUD.generated.h"


// DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventoryItemClick, UInventoryObject*);

/**
 * 
 */
UCLASS()
class SIMPLERPG_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()


public:
	// Declare the event dispatcher
	// FOnInventoryItemClick OnInventoryItemClick;
	
protected:
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UUserWidget* ShopWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* InteractWidget;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HP;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTileView* InventoryWidget;

	
	
};
