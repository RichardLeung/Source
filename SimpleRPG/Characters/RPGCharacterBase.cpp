// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGCharacterBase.h"

#include "RPGNPCCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "HairStrandsCore/Public/GroomComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleRPG/RPGPlayerControllerBase.h"
#include "SimpleRPG/Abilities/RPGAttributeSet.h"
#include "SimpleRPG/Items/Weapon.h"
#include "Components/BoxComponent.h"
#include "SimpleRPG/Components/RPGShopComponent.h"
#include "SimpleRPG/Datas/WeaponData.h"
#include "SimpleRPG/Widgets/GameHUD.h"

// Sets default values
ARPGCharacterBase::ARPGCharacterBase()
{
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

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

	// 实例化ASC
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));

	// Create the attribute set, this replicates by default
	// 创建属性集，这个属性集默认是可以被复制的
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystemComponent)
	{
		// 修改：给ASC赋予技能
		if (HasAuthority() && MyAbilities.Num() > 0)
		{
			for (auto i = 0; i < MyAbilities.Num(); i++)
			{
				if(MyAbilities[i])
				{
					AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(MyAbilities[i].GetDefaultObject(),1,0));
				}
			}
		}

		// 修改：初始化ASC
		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Clear out existing mapping, and add our mapping
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
	ARPGPlayerControllerBase* PlayerController = GetPlayerController();
	if(PlayerController)
	{
		// PlayerController->GameHUD->OnInventoryItemClick.AddDynamic(this,&ARPGCharacterBase::OnInventoryItemClick);
	}
	OnHealthChanged();
}



UAbilitySystemComponent* ARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

// void ARPGCharacterBase::StoreInitialCameraTransform()
// {
// 	InitialCameraLocation = Camera->GetComponentLocation();
// 	InitialCameraRotation = Camera->GetComponentRotation();
// }
//
// void ARPGCharacterBase::RestoreCameraTransform()
// {
// 	TargetCameraLocation = InitialCameraLocation;
// 	TargetCameraRotation = InitialCameraRotation;
// }

// bool ARPGCharacterBase::IsCameraRestored() const
// {
// 	FVector CurrentCameraLocation = Camera->GetComponentLocation();
// 	FRotator CurrentCameraRotation = Camera->GetComponentRotation();
//
// 	// 设置一个阈值，表示摄像头位置和旋转的最小差异
// 	float LocationTolerance = 10.f; // 单位：厘米
// 	float RotationTolerance = 1.f;  // 单位：度
//
// 	// 如果当前摄像头位置和旋转与目标位置和旋转之间的差异小于阈值，则认为摄像头已经还原
// 	return FVector::Dist(CurrentCameraLocation, InitialCameraLocation) <= LocationTolerance &&
// 		   FMath::Abs((CurrentCameraRotation - InitialCameraRotation).GetNormalized().Yaw) <= RotationTolerance &&
// 		   FMath::Abs((CurrentCameraRotation - InitialCameraRotation).GetNormalized().Pitch) <= RotationTolerance &&
// 		   FMath::Abs((CurrentCameraRotation - InitialCameraRotation).GetNormalized().Roll) <= RotationTolerance;
// }

bool ARPGCharacterBase::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}

bool ARPGCharacterBase::CanDisArm()
{
	return bArmWeapon;
}

bool ARPGCharacterBase::CanArm()
{
	return !bArmWeapon;
}

// Called every frame
void ARPGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARPGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* PEI = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PEI->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Move);
		// PEI->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::LookUp);
		// PEI->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Turn);
		// PEI->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Jump);
		PEI->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Attack);
		PEI->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Interact);
		PEI->BindAction(MenuAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Menu);
		PEI->BindAction(MapAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Map);
		PEI->BindAction(TestAction, ETriggerEvent::Triggered, this, &ARPGCharacterBase::Test);
	}
}

void ARPGCharacterBase::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
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

void ARPGCharacterBase::LookUp(const FInputActionValue& Value)
{
	const float LookValue = Value.Get<float>();
	AddControllerYawInput(LookValue);
}

void ARPGCharacterBase::Turn(const FInputActionValue& Value)
{
	const float TurnValue = Value.Get<float>();
	AddControllerPitchInput(TurnValue);
}

void ARPGCharacterBase::Jump()
{
	Super::Jump();
}

void ARPGCharacterBase::PlayAttackMontage()
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
		if(AttackCounter < 2)
		{
			AttackCounter++;
		}else
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

void ARPGCharacterBase::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && EquipAnimMontage)
	{
		AnimInstance->Montage_Play(EquipAnimMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipAnimMontage);
	}
}

void ARPGCharacterBase::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
	bCanChainAttack = true;
	UE_LOG(LogTemp, Warning, TEXT("退出攻击状态"));
	// 设置一个延迟来重置AttackCounter
	GetWorld()->GetTimerManager().SetTimer(ResetAttackCounterTimerHandle, this, &ARPGCharacterBase::ResetAttackCounter, 1.0f, false);
}

void ARPGCharacterBase::Attack(const FInputActionValue& Value)
{
	if(CanAttack())
	{
		if(CanArm())
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

void ARPGCharacterBase::Test()
{
	if(CanArm())
	{
		PlayEquipMontage("Equip");
		bArmWeapon = !bArmWeapon;
		ActionState = EActionState::EAS_Equipping;
	}else if(CanDisArm())
	{
		PlayEquipMontage("Unequip");
		bArmWeapon = !bArmWeapon;
		ActionState = EActionState::EAS_Equipping;
	}
}

void ARPGCharacterBase::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("开始交互"));
	if(InteractIndex > InteractableItems.Num() - 1)
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

void ARPGCharacterBase::Menu()
{
	UE_LOG(LogTemp, Warning, TEXT("菜单"));
	IsShowMenu = !IsShowMenu;
	OnMenuChanged(IsShowMenu);
}

void ARPGCharacterBase::Map()
{
	UE_LOG(LogTemp, Warning, TEXT("地图"));
	IsShowMap = !IsShowMap;
	OnMapChanged(IsShowMap);
}

ARPGPlayerControllerBase* ARPGCharacterBase::GetPlayerController() const
{
	return Cast<ARPGPlayerControllerBase>(GetController());
}

// void ARPGCharacterBase::SetupDialogueCamera(ARPGNPCCharacter* NPC)
// {
// 	if (!NPC) return;
// 	if (IsInteracting)
// 	{
// 		// 如果正在交互，那么恢复摄像头
// 		RestoreCameraTransform();
// 		return;
// 	}
// 	StoreInitialCameraTransform();
// 	FVector PlayerLocation = GetActorLocation();
// 	FVector NPCLocation = NPC->GetActorLocation();
// 	FVector MidPoint = (PlayerLocation + NPCLocation) * 0.5f;
// 	FVector CameraOffset = FVector(100.f, 100.f, 50.f); // 你可以根据需要调整这个值
// 	TargetCameraLocation = MidPoint + CameraOffset;
// 	TargetCameraRotation = UKismetMathLibrary::FindLookAtRotation(TargetCameraLocation, MidPoint);
// 	IsInteracting = true;
// }

void ARPGCharacterBase::Arm()
{
	k2_Arm();
}

void ARPGCharacterBase::DisArm()
{
	k2_DisArm();
}

// void ARPGCharacterBase::OnInventoryItemClick(UInventoryObject* InventoryObject)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("ARPGCharacterBase::OnInventoryItemClick"));
// 	if (InventoryObject)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("ARPGCharacterBase::OnInventoryItemClick %s"), *InventoryObject.);
// 	}	
// }

void ARPGCharacterBase::OnHealthChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("ARPGCharacterBase::OnHealthChanged"));
	K2_OnHealthChanged();
}

void ARPGCharacterBase::OnManaChanged()
{
	UE_LOG(LogTemp, Warning, TEXT("ARPGCharacterBase::OnManaChanged"));
	K2_OnManaChanged();
}

void ARPGCharacterBase::AddInteractableItem(TScriptInterface<IRPGInteractInterface> InteractableItem)
{
	InteractableItems.AddUnique(InteractableItem);
	OnInteractItemsChanged();
}

void ARPGCharacterBase::RemoveInteractableItem(TScriptInterface<IRPGInteractInterface> InteractableItem)
{
	InteractableItems.Remove(InteractableItem);
	OnInteractItemsChanged();
}

void ARPGCharacterBase::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (CurrentWeapon && CurrentWeapon->GetWeaponBox())
	{
		CurrentWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		CurrentWeapon->IgnoreActors.Empty();
	}
}

void ARPGCharacterBase::SetCharacterState(ECharacterState NewState)
{
	CharacterState = NewState;
}

void ARPGCharacterBase::EquipWeapon(UWeaponData* WeaponData)
{
	if(WeaponData)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FVector SpawnLocation = FVector::ZeroVector;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AWeapon* NewWeapon = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);
			if (NewWeapon)
			{
				// Initialize the weapon with the provided ItemData.
				// 使用提供的ItemData初始化武器
				NewWeapon->InitWeapon(WeaponData);
				// Call the Equip method to attach the weapon to the player character.
				// 调用装备方法将武器附加到玩家角色
				NewWeapon->Equip(GetMesh(), FName(TEXT("RightHandSocket")));
				// Set the EquippedWeapon variable.
				if(CurrentWeapon)
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

void ARPGCharacterBase::SetInteractingNPC(ARPGNPCCharacter* NPC)
{
	if (!NPC) return;
	// 设置新的交互NPC
	CurrentInteractingNPC = NPC;
	URPGShopComponent* ShopComponent = NPC->FindComponentByClass<URPGShopComponent>();
	if (!ShopComponent) return;
	TArray<FShopItemInfo> ShopItems = ShopComponent->GetShopItems();
	OnShopChanged(true, ShopItems);
}

void ARPGCharacterBase::SetActionState(EActionState NewState)
{
	ActionState = NewState;
}

void ARPGCharacterBase::ResetAttackCounter()
{
	if (bCanChainAttack)
	{
		AttackCounter = 0;
		bCanChainAttack = false;
	}
}

