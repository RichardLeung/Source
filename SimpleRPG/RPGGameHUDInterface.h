// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "RPGGameHUDInterface.generated.h"

/**
 * Interface for actors that provide a set of RPGItems bound to ItemSlots
 * This exists so RPGCharacterBase can query inventory without doing hacky player controller casts
 * It is designed only for use by native classes
 */
UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class URPGGameHUDInterface : public UInterface
{
	GENERATED_BODY()
};

class SIMPLERPG_API IRPGGameHUDInterface
{
	GENERATED_BODY()

public:
	virtual void OnHealthChanged(float Health) = 0;
	virtual void OnManaChanged(float Mana) = 0;
	virtual void OnInteractItemsChanged(const TArray<class AInteractItem*>& InteractItems) = 0;
};

