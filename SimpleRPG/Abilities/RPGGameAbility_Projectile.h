// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "RPGProjectile.h"
#include "RPGGameAbility_Projectile.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERPG_API URPGGameAbility_Projectile : public URPGGameplayAbility
{
	GENERATED_BODY()
protected:
	// virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<ARPGProjectile> ProjectileClass;
};
