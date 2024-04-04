// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "RPGInteractInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class URPGInteractInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM(BlueprintType)
enum class EInteractableType : uint8
{
	Character UMETA(DisplayName = "Character"),
	Item UMETA(DisplayName = "Item"),
	Interactable UMETA(DisplayName = "WorldStatic"),
};

class SIMPLERPG_API IRPGInteractInterface
{
	GENERATED_BODY()

public:
	// 获取交互对象的类型
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	EInteractableType GetInteractableType() const;

	// 设置交互对象的类型
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interactable")
	void SetInteractableType(EInteractableType NewType);
	
	virtual void OnInteract() = 0;
};

