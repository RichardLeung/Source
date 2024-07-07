// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemySpawnVolume.h"

#include "RPGEnemySpawnPoint.h"
#include "Components/BoxComponent.h"


// Sets default values
ARPGEnemySpawnVolume::ARPGEnemySpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void ARPGEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ARPGEnemySpawnVolume::OnBoxOverlap);
}

void ARPGEnemySpawnVolume::LoadActor_Implementation()
{
	if(bReached)
	{
		Destroy();
	}
}

void ARPGEnemySpawnVolume::OnBoxOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor->ActorHasTag("Player")) return;
	UE_LOG(LogTemp, Warning, TEXT("Player has reached the spawn volume"));
	bReached = true;
	for (ARPGEnemySpawnPoint* Point : SpawnPoints)
	{
		if(IsValid(Point))
		{
			Point->SpawnEnemy();
		}
	}
	Destroy();
}

