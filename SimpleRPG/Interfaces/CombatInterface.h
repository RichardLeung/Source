// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLERPG_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void GetHit(const FVector& ImpactPoint) {
		// 默认实现可以为空
	};

	virtual FVector GetCombatProjectileLocation() {
		// 默认实现可以为空
		return FVector::ZeroVector;
	};

	virtual void OnHealthChanged() {
		// 默认实现可以为空
	};

	virtual void OnManaChanged()
	{
		// 默认实现可以为空
	}

	virtual void OnDie()
	{
		// 默认实现可以为空
	}
};
