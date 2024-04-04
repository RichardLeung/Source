// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CharacterTypes.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "SimpleRPG/Items/Item.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "RPGCharacterBase.generated.h"

class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UGroomComponent;
class UInputMappingContext;
class ARPGPlayerControllerBase;
class UAnimMontage;
class AWeapon;
class UItemData;
class ARPGNPCCharacter;

UCLASS()
class SIMPLERPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

	// ASC本质上是一个UActorComponent,用于处理整个框架下的交互逻辑，包括使用技能（GameplayAbility）、包含属性（AttributeSet）、处理各种效果（GameplayEffect）
	// 修改：声明ASC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GameplayAbilities)
	UAbilitySystemComponent* AbilitySystemComponent; 

	// 修改：实现接口方法
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// 修改：声明Ability数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	TArray<TSubclassOf<UGameplayAbility>> MyAbilities;

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	class URPGAttributeSet* AttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	AWeapon* CurrentWeapon;

	// 当前与玩家交互的NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Interact)
	ARPGNPCCharacter* CurrentInteractingNPC;
	
	UPROPERTY(BlueprintReadOnly, Category = "Interactable")
	TArray<TScriptInterface<IRPGInteractInterface>> InteractableItems;

	bool IsInteracting = false;

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* LookUpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* TurnAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* AttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* MenuAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* MapAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	UInputAction* TestAction;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, Category=Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category=Hair)
	UGroomComponent* Eyebrows;
	
	int32 InteractIndex = 0;

	bool IsShowMenu = false;

	bool IsShowMap = false;

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.f;

	FTimerHandle ResetAttackCounterTimerHandle;

	FTimerHandle DisarmWeaponTimerHandle;

	/**
	 * Callbacks for input actions
	 */
	void Move(const FInputActionValue& Value);

	void LookUp(const FInputActionValue& Value);

	void Turn(const FInputActionValue& Value);

	virtual void Jump() override;

	UFUNCTION(BlueprintCallable, Category = "Input", meta = (AllowPrivateAccess = "true"))
	void Attack(const FInputActionValue& Value);

	void Interact();

	void Menu();
	
	void Map();

	void Test();
	
	ARPGPlayerControllerBase* GetPlayerController() const;
	
	int32 AttackCounter = 0;
	
	bool bCanChainAttack = false;

	bool bArmWeapon = true;

	bool CanAttack();

	bool CanDisArm();

	bool CanArm();
	
	/**
	 * Play montage function
	 */
	void PlayAttackMontage();

	void PlayEquipMontage(const FName& SectionName);

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void AttackEnd();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void Arm();

	UFUNCTION(BlueprintCallable, Category = "Animation")
	void DisArm();

	// void OnInventoryItemClick(UInventoryObject* InventoryObject);
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void k2_Arm();
	
	UFUNCTION(BlueprintImplementableEvent)
	void k2_DisArm();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInteractItemsChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnInventoryItemsChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMenuChanged(bool IsShow);

	UFUNCTION(BlueprintImplementableEvent)
	void OnShopChanged(bool IsShow, const TArray<FShopItemInfo>& ShopItems);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnMapChanged(bool IsShow);
	
	virtual void OnHealthChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_OnHealthChanged();

	virtual void OnManaChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void K2_OnManaChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTest();

	void AddInteractableItem(TScriptInterface<IRPGInteractInterface> InteractableItem);

	void RemoveInteractableItem(TScriptInterface<IRPGInteractInterface> InteractableItem);

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
	UFUNCTION(BlueprintCallable)
	void SetCharacterState(ECharacterState NewState);

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(UWeaponData* ItemData);

	UFUNCTION(BlueprintCallable)
	void SetInteractingNPC(ARPGNPCCharacter* NPC);

	UFUNCTION(BlueprintCallable)
	void SetActionState(EActionState NewState);

	void ResetAttackCounter();

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	/**
	 * Animation Montages
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Montages)
	UAnimMontage* AttackAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Montages)
	UAnimMontage* EquipAnimMontage;
};
