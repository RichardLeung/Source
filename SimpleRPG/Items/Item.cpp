// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "SimpleRPG/RPGPlayerControllerBase.h"
#include "SimpleRPG/Characters/RPGCharacterBase.h"
#include "SimpleRPG/Datas/ItemData.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(Scene);

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(Scene);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Scene);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}


void AItem::OnInteract()
{
	UE_LOG(LogTemp, Warning, TEXT("AItem Interact：%s"), *this->GetName());
	ARPGPlayerControllerBase *PlayerController = Cast<ARPGPlayerControllerBase>(GetWorld()->GetFirstPlayerController());
	if(PlayerController)
	{
		if(ItemData->ItemType == EItemType::Weapon)
		{
			PlayerController->AddInventoryItem(ItemData);
			UE_LOG(LogTemp, Warning, TEXT("拾取物品"));
			Destroy();
		}
	}
}

void AItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARPGCharacterBase* PlayerCharacter = Cast<ARPGCharacterBase>(OtherActor))
	{
		AItem *Item = Cast<AItem>(this);
		TScriptInterface<IRPGInteractInterface> InteractableInterface;
		InteractableInterface.SetInterface(Cast<IRPGInteractInterface>(Item));
		InteractableInterface.SetObject(Item);
		InteractableInterface->Execute_SetInteractableType(InteractableInterface.GetObject(), EInteractableType::Item);
		PlayerCharacter->AddInteractableItem(InteractableInterface);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARPGCharacterBase* PlayerCharacter = Cast<ARPGCharacterBase>(OtherActor))
	{
		AItem *Item = Cast<AItem>(this);
		TScriptInterface<IRPGInteractInterface> InteractableInterface;
		InteractableInterface.SetInterface(Cast<IRPGInteractInterface>(Item));
		InteractableInterface.SetObject(Item);
		InteractableInterface->Execute_SetInteractableType(InteractableInterface.GetObject(), EInteractableType::Item);
		PlayerCharacter->RemoveInteractableItem(InteractableInterface);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

