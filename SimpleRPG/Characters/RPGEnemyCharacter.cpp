// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemyCharacter.h"

#include "RPGCharacterBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ARPGEnemyCharacter::ARPGEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera,ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera,ECollisionResponse::ECR_Ignore);
}

void ARPGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ARPGCharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ARPGEnemyCharacter::PlayHitMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && HitAnimMontage)
	{
		AnimInstance->Montage_Play(HitAnimMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitAnimMontage);
	}
}

void ARPGEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARPGEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARPGEnemyCharacter::DirectionalHit(const FVector& ImpactPoint)
{
	// // 按照攻击部位播放不同的动画
	// FVector Forward = GetActorForwardVector();
	// const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	// FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	//
	// // Forward * ToHit = |Forward||ToHit| * cos(theta)
	// // |Forward| = 1, |ToHit| = 1, So Forward * ToHit = cos(theta)
	// const double CosTheta = FVector::DotProduct(ToHit, Forward);
	//
	// // Take the inverse cosine (arc - cosine) of cos(theta) to get theta
	// double Theta = FMath::Acos(CosTheta);
	//
	// // convert from radians to degree
	// Theta = FMath::RadiansToDegrees(Theta);
	//
	// // If CrossProduct points down, Theta is negative
	// const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	// if(CrossProduct.Z < 0)
	// {
	// 	Theta = -Theta;
	// }
	// FName SectionName("FromBack");
	// if(Theta >= -45.f && Theta < 45.f)
	// {
	// 	SectionName = FName("FromFront");
	// }
	// else if(Theta >= 45.f && Theta < 135.f)
	// {
	// 	SectionName = FName("FromRight");
	// }
	// else if(Theta >= -135.f && Theta < -45.f)
	// {
	// 	SectionName = FName("FromLeft");
	// }

	//按照角色站位播放不同的动画
	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector DirectionToEnemy = EnemyLocation - PlayerLocation;
	float AngleToEnemy = FMath::RadiansToDegrees(FMath::Atan2(DirectionToEnemy.Y, DirectionToEnemy.X));
	FName SectionName("FromBack");
	if (AngleToEnemy > -45 && AngleToEnemy < 45) {
		// 在角色前面
		SectionName = FName("FromFront");
	} else if (AngleToEnemy >= 45 && AngleToEnemy < 135) {
		// 在角色右边
		SectionName = FName("FromRight");
	} else if (AngleToEnemy >= -135 && AngleToEnemy < -45) {
		// 在角色左边
		SectionName = FName("FromLeft");
	} else {
		// 在角色后面
	}
	
	PlayHitMontage(SectionName);
}

void ARPGEnemyCharacter::GetHit(const FVector& ImpactPoint)
{
	DirectionalHit(ImpactPoint);
}


