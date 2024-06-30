// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGEnemyCharacter.h"
#include "RPGPlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleRPG/SimpleRPG.h"
#include "SimpleRPG/Abilities/RPGAttributeSet.h"
#include "SimpleRPG/AI/RPGAIController.h"

ARPGEnemyCharacter::ARPGEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_Enemy);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));

	StatusBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusBar"));
	StatusBar->SetupAttachment(GetRootComponent());
}

void ARPGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ARPGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (AbilitySystemComponent)
	{
		// 修改：给ASC赋予技能
		if (MyAbilities.Num() > 0)
		{
			for (auto i = 0; i < MyAbilities.Num(); i++)
			{
				if (MyAbilities[i])
				{
					AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MyAbilities[i].GetDefaultObject(), 1, 0));
				}
			}
		}

		// 修改：初始化ASC
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ARPGEnemyCharacter::PlayHitMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitAnimMontage)
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

void ARPGEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	RPGAIController = Cast<ARPGAIController>(NewController);
	if (RPGAIController && BehaviorTree)
	{
		RPGAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		RPGAIController->RunBehaviorTree(BehaviorTree);
	}
}

void ARPGEnemyCharacter::DirectionalHit(const FVector& ImpactPoint)
{
	//按照角色站位播放不同的动画
	FVector EnemyLocation = GetActorLocation();
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	FVector DirectionToEnemy = EnemyLocation - PlayerLocation;
	float AngleToEnemy = FMath::RadiansToDegrees(FMath::Atan2(DirectionToEnemy.Y, DirectionToEnemy.X));
	FName SectionName("FromBack");
	if (AngleToEnemy > -45 && AngleToEnemy < 45)
	{
		// 在角色前面
		SectionName = FName("FromFront");
	}
	else if (AngleToEnemy >= 45 && AngleToEnemy < 135)
	{
		// 在角色右边
		SectionName = FName("FromRight");
	}
	else if (AngleToEnemy >= -135 && AngleToEnemy < -45)
	{
		// 在角色左边
		SectionName = FName("FromLeft");
	}
	else
	{
		// 在角色后面
	}

	PlayHitMontage(SectionName);
}

void ARPGEnemyCharacter::GetHit(const FVector& ImpactPoint)
{
	DirectionalHit(ImpactPoint);
}

void ARPGEnemyCharacter::OnHealthChanged()
{
	K2_OnHealthChanged();
}

void ARPGEnemyCharacter::OnDie()
{
	K2_OnDie();
}
