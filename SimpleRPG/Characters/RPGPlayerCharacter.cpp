// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HairStrandsCore/Public/GroomComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "SimpleRPG/RPGPlayerControllerBase.h"
#include "SimpleRPG/Abilities/RPGAttributeSet.h"
#include "SimpleRPG/Items/Weapon.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "SimpleRPG/SimpleRPG.h"
#include "RPGNPCCharacter.h"
#include "SimpleRPG/Abilities/RPGAbilitySystemComponent.h"
#include "SimpleRPG/Components/RPGShopComponent.h"
#include "SimpleRPG/Datas/WeaponData.h"
#include "SimpleRPG/Widgets/GameHUD.h"


// Sets default values
ARPGPlayerCharacter::ARPGPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

	// 实例化ASC
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("Ability System Component"));

	// Create the attribute set, this replicates by default
	// 创建属性集，这个属性集默认是可以被复制的
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void ARPGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AbilitySystemComponent)
	{
		// 修改：给ASC赋予技能
		if (HasAuthority() && MyAbilities.Num() > 0)
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
		// InitBaseStatsAttributes();
	}
	OnHealthChanged();
}

void ARPGPlayerCharacter::InitBaseStatsAttributes() const
{
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(DefaultBaseStatsAttributesEffect, 1, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

UAbilitySystemComponent* ARPGPlayerCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// Called every frame
void ARPGPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ARPGPlayerCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool ARPGPlayerCharacter::CanDisArm()
{
	return bArmWeapon;
}

bool ARPGPlayerCharacter::CanArm()
{
	return !bArmWeapon;
}

// // Called to bind functionality to input
// void ARPGPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// 	if (UEnhancedInputComponent* PEI = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
// 	{
// 		PEI->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Move);
// 		PEI->BindAction(MenuAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Menu);
// 		PEI->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Attack);
// 		PEI->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Interact);
// 		PEI->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Inventory);
// 		PEI->BindAction(SkillAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Skill);
// 		PEI->BindAction(UltimateAction, ETriggerEvent::Triggered, this, &ARPGPlayerCharacter::Ultimate);
// 	}
// }

void ARPGPlayerCharacter::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied)
	{
		return;
	}
	if (GetController() != nullptr)
	{
		const FVector2D MoveAxisVector = Value.Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MoveAxisVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MoveAxisVector.X);
	}
}

void ARPGPlayerCharacter::LookUp(const FInputActionValue& Value)
{
	const float LookValue = Value.Get<float>();
	AddControllerYawInput(LookValue);
}

void ARPGPlayerCharacter::Turn(const FInputActionValue& Value)
{
	const float TurnValue = Value.Get<float>();
	AddControllerPitchInput(TurnValue);
}

void ARPGPlayerCharacter::Jump()
{
	Super::Jump();
}

void ARPGPlayerCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	if (!bCanChainAttack)
	{
		AttackCounter = 0;
		FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), AttackCounter));
		UE_LOG(LogTemp, Warning, TEXT("播放攻击0动画"));
		AnimInstance->Montage_Play(AttackAnimMontage);
		AnimInstance->Montage_JumpToSection(SectionName, AttackAnimMontage);
	}
	else
	{
		if (AttackCounter < 2)
		{
			AttackCounter++;
		}
		else
		{
			ResetAttackCounter();
		}
		UE_LOG(LogTemp, Warning, TEXT("播放攻击%d动画"), AttackCounter);
		// 根据AttackCounter的值播放相应的攻击动画
		FName SectionName = FName(*FString::Printf(TEXT("Attack%d"), AttackCounter));
		AnimInstance->Montage_Play(AttackAnimMontage);
		AnimInstance->Montage_JumpToSection(SectionName, AttackAnimMontage);
	}
	bCanChainAttack = false;
}

void ARPGPlayerCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipAnimMontage)
	{
		AnimInstance->Montage_Play(EquipAnimMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipAnimMontage);
	}
}

void ARPGPlayerCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
	bCanChainAttack = true;
	UE_LOG(LogTemp, Warning, TEXT("退出攻击状态"));
	// 设置一个延迟来重置AttackCounter
	GetWorld()->GetTimerManager().SetTimer(ResetAttackCounterTimerHandle, this,
	                                       &ARPGPlayerCharacter::ResetAttackCounter, 1.0f, false);
}

void ARPGPlayerCharacter::Attack(const FInputActionValue& Value)
{
	if (CanAttack())
	{
		if (CanArm())
		{
			Test();
			return;
		}
		// 在攻击之前，先检查是否有有效的重置计时器，如果有则取消它
		if (GetWorld()->GetTimerManager().IsTimerActive(ResetAttackCounterTimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(ResetAttackCounterTimerHandle);
		}
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void ARPGPlayerCharacter::Test()
{
	if (CanArm())
	{
		PlayEquipMontage("Equip");
		bArmWeapon = !bArmWeapon;
		ActionState = EActionState::EAS_Equipping;
	}
	else if (CanDisArm())
	{
		PlayEquipMontage("Unequip");
		bArmWeapon = !bArmWeapon;
		ActionState = EActionState::EAS_Equipping;
	}
}

void ARPGPlayerCharacter::Inventory()
{
	k2_Inventory();
}

void ARPGPlayerCharacter::Skill()
{
	k2_Skill();
}

void ARPGPlayerCharacter::Ultimate()
{
	k2_Ultimate();
}

void ARPGPlayerCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("开始交互"));
	if (InteractIndex > InteractableItems.Num() - 1)
	{
		return;
	}
	// 获取交互物
	TScriptInterface<IRPGInteractInterface> Interactable = InteractableItems[InteractIndex];
	IRPGInteractInterface* InteractableInterface = Cast<IRPGInteractInterface>(Interactable.GetInterface());
	// 获取 IInteractableInterface
	if (InteractableInterface)
	{
		// 调用 OnInteract 方法
		InteractableInterface->OnInteract();
	}
}

ARPGPlayerControllerBase* ARPGPlayerCharacter::GetPlayerController() const
{
	return Cast<ARPGPlayerControllerBase>(GetController());
}

void ARPGPlayerCharacter::Arm()
{
	k2_Arm();
}

void ARPGPlayerCharacter::DisArm()
{
	k2_DisArm();
}

void ARPGPlayerCharacter::OnHealthChanged()
{
	K2_OnHealthChanged();
}

void ARPGPlayerCharacter::OnManaChanged()
{
	K2_OnManaChanged();
}

void ARPGPlayerCharacter::AddInteractableItem(TScriptInterface<IRPGInteractInterface> InteractableItem)
{
	InteractableItems.AddUnique(InteractableItem);
	OnInteractItemsChanged();
}

void ARPGPlayerCharacter::RemoveInteractableItem(TScriptInterface<IRPGInteractInterface> InteractableItem)
{
	InteractableItems.Remove(InteractableItem);
	OnInteractItemsChanged();
}

void ARPGPlayerCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (CurrentWeapon && CurrentWeapon->GetWeaponBox())
	{
		CurrentWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		CurrentWeapon->IgnoreActors.Empty();
	}
}

void ARPGPlayerCharacter::SetCharacterState(ECharacterState NewState)
{
	CharacterState = NewState;
}

void ARPGPlayerCharacter::EquipWeapon(UWeaponData* WeaponData)
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
				// Set the character state to EquippedOneHandedWeapon.
				// 将角色状态设置为装备单手武器
				SetCharacterState(ECharacterState::ECS_EquippedOneHandedWeapon);
			}
		}
	}
}

void ARPGPlayerCharacter::SetInteractingNPC(ARPGNPCCharacter* NPC)
{
	if (!NPC)
	{
		return;
	}
	// 设置新的交互NPC
	CurrentInteractingNPC = NPC;
	URPGShopComponent* ShopComponent = NPC->FindComponentByClass<URPGShopComponent>();
	if (!ShopComponent)
	{
		return;
	}
	TArray<FShopItemInfo> ShopItems = ShopComponent->GetShopItems();
	OnShopChanged(true, ShopItems);
}

void ARPGPlayerCharacter::SetActionState(EActionState NewState)
{
	ActionState = NewState;
}

void ARPGPlayerCharacter::ResetAttackCounter()
{
	if (bCanChainAttack)
	{
		AttackCounter = 0;
		bCanChainAttack = false;
	}
}

FVector ARPGPlayerCharacter::GetCombatProjectileLocation()
{
	FVector CombatSocketLocation = GetActorLocation();
	CombatSocketLocation.Z -= 70.f;
	CombatSocketLocation.X += 50.f;
	return CombatSocketLocation;
}
