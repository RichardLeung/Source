// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "SimpleRPG/Interfaces/HitInterface.h"
#include "RPGEnemyCharacter.generated.h"

class UAnimMontage;
class UWidgetComponent;

UCLASS()
class SIMPLERPG_API ARPGEnemyCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ARPGEnemyCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DirectionalHit(const FVector& ImpactPoint);

	virtual void GetHit(const FVector& ImpactPoint) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities)
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities)
	TObjectPtr<UWidgetComponent> StatusBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Abilities)
	TArray<TSubclassOf<UGameplayAbility>> MyAbilities;


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
	class ARPGCharacterBase* PlayerCharacter;
};
