// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "RPGCharacterBase.generated.h"

UCLASS()
class SIMPLERPG_API ARPGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
