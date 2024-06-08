// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGCharacterBase.h"
#include "RPGEnemyCharacter.generated.h"

class UAnimMontage;
class UWidgetComponent;

UCLASS()
class SIMPLERPG_API ARPGEnemyCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()

public:
	ARPGEnemyCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities)
	TObjectPtr<UWidgetComponent> StatusBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Abilities)
	TArray<TSubclassOf<UGameplayAbility>> MyAbilities;

	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	class URPGAttributeSet* AttributeSet;

protected:
	virtual void BeginPlay() override;

	/**
	 *  Play Animation Montage
	 */
	void PlayHitMontage(const FName& SectionName);

public:
	/**
	 * Animation Montages
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Montages)
	UAnimMontage* HitAnimMontage;


private:
	UPROPERTY()
	class ARPGPlayerCharacter* PlayerCharacter;
};
