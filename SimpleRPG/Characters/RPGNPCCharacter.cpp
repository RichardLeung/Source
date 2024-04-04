// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGNPCCharacter.h"
#include "RPGCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleRPG/RPGGameInstanceBase.h"
#include "SimpleRPG/RPGPlayerControllerBase.h"

// Sets default values
ARPGNPCCharacter::ARPGNPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(GetRootComponent());

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Sphere->SetupAttachment(GetRootComponent());
	Sphere->SetSphereRadius(InteractRange);
}


void ARPGNPCCharacter::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if (ARPGCharacterBase* Interactable = Cast<ARPGCharacterBase>(OtherActor))
	{
		ARPGNPCCharacter *Item = Cast<ARPGNPCCharacter>(this);
		TScriptInterface<IRPGInteractInterface> InteractableInterface;
		InteractableInterface.SetInterface(Cast<IRPGInteractInterface>(Item));
		InteractableInterface.SetObject(Item);
		InteractableInterface->Execute_SetInteractableType(InteractableInterface.GetObject(), EInteractableType::Character);
		PlayerCharacter->AddInteractableItem(InteractableInterface);
	}
}

void ARPGNPCCharacter::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARPGCharacterBase* Interactable = Cast<ARPGCharacterBase>(OtherActor))
	{
		ARPGNPCCharacter *Item = Cast<ARPGNPCCharacter>(this);
		TScriptInterface<IRPGInteractInterface> InteractableInterface;
		InteractableInterface.SetInterface(Cast<IRPGInteractInterface>(Item));
		InteractableInterface.SetObject(Item);
		InteractableInterface->Execute_SetInteractableType(InteractableInterface.GetObject(), EInteractableType::Character);
		PlayerCharacter->RemoveInteractableItem(InteractableInterface);
	}
}

// Called when the game starts or when spawned
void ARPGNPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ARPGCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARPGNPCCharacter::OnSphereBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARPGNPCCharacter::OnSphereEndOverlap);
}

// Called every frame
void ARPGNPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (InShowRange())
	{
		WidgetComponent->SetVisibility(true);
		FVector LookAtTarget = PlayerCharacter->Camera->GetComponentLocation();
		FVector ToTarget = LookAtTarget - GetActorLocation();
		FRotator LookAtRotation = FRotator(0.f,ToTarget.Rotation().Yaw,0.f);
		WidgetComponent->SetWorldRotation(
			FMath::RInterpTo(WidgetComponent->GetComponentRotation(),LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(GetWorld()),5.f));
	}else
	{
		WidgetComponent->SetVisibility(false);
	}
}

// Called to bind functionality to input
void ARPGNPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARPGNPCCharacter::OnInteract()
{
	if(PlayerCharacter)
	{
		k2_OnInteract();
	}
	
}

bool ARPGNPCCharacter::InShowRange()
{
	if(PlayerCharacter)
	{
		float Distance = FVector::Dist(GetActorLocation(),PlayerCharacter->GetActorLocation());
		// Check to see if Tank is in range
		if(Distance <= ShowRange && Distance >= InteractRange)
		{
			// If in range, rotate turret toward Tank
			return true;
		}
	}
	return false;
}

