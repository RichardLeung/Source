// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_InitCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERPG_API UExecCalc_InitCharacter : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UExecCalc_InitCharacter();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
