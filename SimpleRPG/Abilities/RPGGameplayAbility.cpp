// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SimpleRPG/Characters/RPGCharacterBase.h"

class ARPGCharacterBase;

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ActivateAbility(C++)"));
}

void URPGGameplayAbility::StopMovement() const
{
	// 通过GetActorInfo获取获取当前角色
	ARPGCharacterBase* AvatarCharacter = Cast<ARPGCharacterBase>(GetActorInfo().AvatarActor.Get());
	AvatarCharacter->GetCharacterMovement()->DisableMovement();
}

void URPGGameplayAbility::RefreshMovement() const
{
    // 通过GetActorInfo获取获取当前角色
	ARPGCharacterBase* AvatarCharacter = Cast<ARPGCharacterBase>(GetActorInfo().AvatarActor.Get());
	AvatarCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}
