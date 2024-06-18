// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class SIMPLERPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARPGGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "角色数据表")
	TObjectPtr<UDataTable> DataTableCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "升级经验数据表")
	TObjectPtr<UDataTable> DataTableLevelExp;

	virtual void PawnKilled(APawn* PawnKilled);

	virtual void EndGame(bool bIsPlayerWinner);
};
