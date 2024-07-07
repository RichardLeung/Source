// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "RPGEnemySpawnPoint.generated.h"

class ARPGEnemyCharacter;

UCLASS()
class SIMPLERPG_API ARPGEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "敌人")
	TSubclassOf<ARPGEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "敌人")
	int32 EnemyLevel = 1;
};

