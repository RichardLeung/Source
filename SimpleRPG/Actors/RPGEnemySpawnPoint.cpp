// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemySpawnPoint.h"
#include "SimpleRPG/Characters/RPGEnemyCharacter.h"


void ARPGEnemySpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ARPGEnemyCharacter* Enemy = GetWorld()->SpawnActorDeferred<ARPGEnemyCharacter>(EnemyClass, GetActorTransform());
	Enemy->Level = 1;
	Enemy->FinishSpawning(GetActorTransform());
	Enemy->SpawnDefaultController();
}
