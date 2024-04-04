// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARPGGameModeBase();

public:
	virtual void PawnKilled(APawn* PawnKilled);

	virtual void EndGame(bool bIsPlayerWinner);
};
