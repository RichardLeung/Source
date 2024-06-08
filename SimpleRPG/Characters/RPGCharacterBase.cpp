// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterBase.h"

// Sets default values
ARPGCharacterBase::ARPGCharacterBase()
{
	
}

// Called when the game starts or when spawned
void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ARPGCharacterBase::GetCombatProjectileLocation()
{
	return ICombatInterface::GetCombatProjectileLocation();
}



