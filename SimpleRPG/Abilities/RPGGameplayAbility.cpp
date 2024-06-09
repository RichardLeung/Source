// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility.h"

#include "Kismet/KismetSystemLibrary.h"

void URPGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo,
                                          const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("ActivateAbility(C++)"));
}
