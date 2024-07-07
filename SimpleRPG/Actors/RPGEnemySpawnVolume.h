// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleRPG/Interfaces/SaveInterface.h"
#include "RPGEnemySpawnVolume.generated.h"

class UBoxComponent;
class RPGEnemySpawnPoint;

UCLASS()
class SIMPLERPG_API ARPGEnemySpawnVolume : public AActor, public ISaveInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARPGEnemySpawnVolume();

	bool bReached = false;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void LoadActor_Implementation() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<ARPGEnemySpawnPoint*> SpawnPoints;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

	
};
