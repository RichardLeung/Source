// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "RPGCharacterBase.h"
#include "RPGEnemyCharacter.generated.h"

class UAnimMontage;
class UWidgetComponent;
class UBehaviorTree;
class ARPGAIController;
class AWeapon;
class UWeaponData;

UCLASS()
class SIMPLERPG_API ARPGEnemyCharacter : public ARPGCharacterBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARPGEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	void DirectionalHit(const FVector& ImpactPoint);

	virtual void GetHit(const FVector& ImpactPoint) override;

	virtual void OnHealthChanged() override;

	UFUNCTION(BlueprintImplementableEvent)
	void K2_OnHealthChanged();

	virtual void OnDie() override;

	UFUNCTION(BlueprintImplementableEvent)
	void K2_OnDie();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities) 
	UAbilitySystemComponent* AbilitySystemComponent;

	// 修改：实现接口方法
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities)
	TObjectPtr<UWidgetComponent> StatusBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Abilities)
	TArray<TSubclassOf<UGameplayAbility>> MyAbilities;

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	class URPGAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Combat)
	float LifeSpan = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Weapon)
	AWeapon* CurrentWeapon;

	UFUNCTION(BlueprintCallable)
	void EquipWeapon(UWeaponData* ItemData);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon)
	FName WeaponName;
	
protected:
	virtual void BeginPlay() override;

	/**
	 *  Play Animation Montage
	 */
	void PlayHitMontage(const FName& SectionName);

	// 暂停移动
	UFUNCTION(BlueprintCallable)
	void StopMovement() const;

	UFUNCTION(BlueprintCallable)
	void RefreshMovement() const;

	void DistortActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=AI)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ARPGAIController> RPGAIController;

public:
	/**
	 * Animation Montages
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Montages)
	UAnimMontage* HitAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Montages)
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Montages)
	UAnimMontage* AttackAnimMontage;

private:
	UPROPERTY()
	class ARPGPlayerCharacter* PlayerCharacter;
};
