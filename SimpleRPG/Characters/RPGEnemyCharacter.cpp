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
#include "SimpleRPG/RPGGameInstanceBase.h"
#include "SimpleRPG/RPGGameplayTags.h"
#include "SimpleRPG/RPGPlayerControllerBase.h"
#include "SimpleRPG/SimpleRPG.h"
#include "SimpleRPG/Abilities/RPGAttributeSet.h"
#include "SimpleRPG/AI/RPGAIController.h"
#include "SimpleRPG/Datas/WeaponData.h"
#include "SimpleRPG/Items/Weapon.h"

ARPGEnemyCharacter::ARPGEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECC_Enemy);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));

	StatusBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusBar"));
	StatusBar->SetupAttachment(GetRootComponent());
}

void ARPGEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
	PlayerCharacter = Cast<ARPGPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (WeaponName != NAME_None)
	{
		// 获取GameInstance
		URPGGameInstanceBase* GameInstance = Cast<URPGGameInstanceBase>(GetGameInstance());
		if (GameInstance)
		{
			// 获取武器数据
			FWeaponBaseModel WeaponModel = GameInstance->GetWeaponData(WeaponName);
			UWeaponData* WeaponData = Cast<UWeaponData>(WeaponModel.WeaponData.LoadSynchronous());
			if (WeaponData)
			{
				EquipWeapon(WeaponData);
			}
		}
	}
}

// 假设这个函数在您的角色类中
void ARPGEnemyCharacter::ActivateSpecificAbility(FGameplayTag AbilityTag)
{
	// 获取 AbilitySystemComponent
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC) return;

	// 遍历 MyAbilities 数组
	for (TSubclassOf<UGameplayAbility> AbilityClass : MyAbilities)
	{
		// 获取默认对象
		if (UGameplayAbility* AbilityCDO = AbilityClass.GetDefaultObject())
		{
			// 检查这个能力是否匹配我们要找的标签
			if (AbilityCDO->AbilityTags.HasTag(AbilityTag))
			{
				// 找到匹配的能力，现在激活它
				FGameplayAbilitySpecHandle Handle = ASC->GiveAbility(
					FGameplayAbilitySpec(AbilityClass, 1, INDEX_NONE, this));
                
				ASC->TryActivateAbility(Handle);
                
				// 我们已经激活了能力，所以可以退出循环
				break;
			}
		}
	}
}

void ARPGEnemyCharacter::PlayHitMontage(const FName& SectionName)
{
	if(AttributeSet->HPCurrent.GetCurrentValue() == 0.f)
	{
		ActivateSpecificAbility(FRPGGameplayTags::Get().Abilities_EnemyDeath);
		return;
	}
	ActivateSpecificAbility(FRPGGameplayTags::Get().Abilities_HitReact);
	// 设置定时器在动画结束时重新启用移动
	// FTimerHandle TimerHandle;
	// GetWorldTimerManager().SetTimer(TimerHandle, this, &ARPGEnemyCharacter::RefreshMovement, HitAnimMontage->GetPlayLength(), false);
}

void ARPGEnemyCharacter::StopMovement() const
{
	// 停止移动
	GetCharacterMovement()->DisableMovement();
	// 设置黑板值
	UBlackboardComponent* BlackboardComponent = RPGAIController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsEnum(FName("EnemyState"), 2);
}

void ARPGEnemyCharacter::RefreshMovement() const
{
	// 恢复移动
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	// 设置黑板值
	UBlackboardComponent* BlackboardComponent = RPGAIController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsEnum(FName("EnemyState"), 0);
}

void ARPGEnemyCharacter::DistortActor()
{
	Destroy();
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
	// 设置黑板值
	UBlackboardComponent* BlackboardComponent = RPGAIController->GetBlackboardComponent();
	BlackboardComponent->SetValueAsEnum(FName("EnemyState"), 3);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(LifeSpan);
	K2_OnDie();
}

UAbilitySystemComponent* ARPGEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGEnemyCharacter::EquipWeapon(UWeaponData* WeaponData)
{
	if (WeaponData)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FVector SpawnLocation = FVector::ZeroVector;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AWeapon* NewWeapon = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, SpawnRotation,
			SpawnParams);
			if (NewWeapon)
			{
				// Initialize the weapon with the provided ItemData.
				// 使用提供的ItemData初始化武器
				NewWeapon->InitWeapon(WeaponData);
				// Call the Equip method to attach the weapon to the player character.
				// 调用装备方法将武器附加到玩家角色
				NewWeapon->Equip(GetMesh(), FName(TEXT("RightHandSocket")));
				// Set the EquippedWeapon variable.
				if (CurrentWeapon)
				{
					CurrentWeapon->Destroy();
				}
				// 设置装备武器变量
				CurrentWeapon = NewWeapon;
			}
		}
	}
}
