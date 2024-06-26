// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGCharacterBase.h"
#include "SimpleRPG/Interfaces/HitInterface.h"
#include "RPGEnemyCharacter.generated.h"

class UAnimMontage;
class UWidgetComponent;

UCLASS()
class SIMPLERPG_API ARPGEnemyCharacter : public ARPGCharacterBase, public IHitInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARPGEnemyCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	void DirectionalHit(const FVector& ImpactPoint);

	virtual void GetHit(const FVector& ImpactPoint) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Abilities)
	UAbilitySystemComponent* AbilitySystemComponent;

	// 修改：实现接口方法
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

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
	class ARPGPlayerCharacter* PlayerCharacter;
};
