// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SimpleRPG/Interfaces/HitInterface.h"
#include "SimpleRPG/Datas/WeaponData.h"

AWeapon::AWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SetRootComponent(SkeletalMesh);

	WeaponBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Collision"));
	WeaponBox->SetupAttachment(GetRootComponent());
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	WeaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxTraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Box Start"));
	BoxTraceStart->SetupAttachment(GetRootComponent());

	BoxTraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("Box End"));
	BoxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::InitWeapon(UWeaponData* ItemData)
{
	if (ItemData)
	{
		WeaponData = ItemData;
		if(WeaponData)
		{
			UE_LOG(LogTemp, Warning, TEXT("InitWeapon: %s"), *ItemData->GetPrimaryAssetId().ToString());
			SkeletalMesh->SetSkeletalMesh(WeaponData->WeaponSkeletalMesh);
			WeaponBox->SetRelativeLocation(WeaponData->WeaponCollisionLocation);
			WeaponBox->SetBoxExtent(WeaponData->WeaponBoxExtent);
			WeaponBox->SetRelativeScale3D(WeaponData->WeaponCollisionScale);
			BoxTraceStart->SetRelativeLocation(WeaponData->WeaponBoxStart);
			BoxTraceEnd->SetRelativeLocation(WeaponData->WeaponBoxEnd);
		}
	}
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	SkeletalMesh->AttachToComponent(InParent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true), InSocketName);
}

void AWeapon::SetEnableCollision(ECollisionEnabled::Type NewCollisionEnabled)
{
	if(WeaponBox)
	{
		WeaponBox->SetCollisionEnabled(NewCollisionEnabled);
	}
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlapBegin);
}

void AWeapon::OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = BoxTraceStart->GetComponentLocation();
	const FVector End = BoxTraceEnd->GetComponentLocation();
	// const FCollisionQueryParams Params = FCollisionQueryParams(FName(TEXT("Weapon Trace")), true, this);
	// const FCollisionResponseParams ResponseParams = FCollisionResponseParams(ECR_Block);
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	for (AActor* Actor : IgnoreActors)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(5.f,5.f,5.f),
		BoxTraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		5.f);
	if(HitResult.GetActor())
	{
		IHitInterface* HitInterface = Cast<IHitInterface>(HitResult.GetActor());
		if(HitInterface)
		{
			HitInterface->GetHit(HitResult.ImpactPoint);
		}
		IgnoreActors.AddUnique(HitResult.GetActor());
	}
}


