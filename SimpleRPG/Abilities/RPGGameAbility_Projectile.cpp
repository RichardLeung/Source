// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameAbility_Projectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "RPGProjectile.h"
#include "SimpleRPG/RPGGameplayTags.h"
#include "SimpleRPG/Interfaces/CombatInterface.h"

void URPGGameAbility_Projectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo,
                                                 const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void URPGGameAbility_Projectile::SpawnProjectile()
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		FVector CombatSocketLocation = CombatInterface->GetCombatProjectileLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(CombatSocketLocation);
		// 获取角色的前方向量
		FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
		// 设置角色的前方向量
		SpawnTransform.SetRotation(ForwardVector.ToOrientationQuat());

		ARPGProjectile* Projectile = GetWorld()->SpawnActorDeferred<ARPGProjectile>(
			ProjectileClass, SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(
			GetAvatarActorFromActorInfo());
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
			GameplayEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
		
		FRPGGameplayTags GameplayTags = FRPGGameplayTags::Get();
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_BaseStats_HPCurrent, -50.0f);
		Projectile->DamageEffectSpecHandle = SpecHandle;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
