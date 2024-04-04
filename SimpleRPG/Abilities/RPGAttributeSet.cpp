// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "SimpleRPG/Characters/RPGCharacterBase.h"


URPGAttributeSet::URPGAttributeSet()
	: Health(100.f)
	, MaxHealth(100.f)
	, Mana(50.f)
	, MaxMana(50.f)
{
}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Strength, COND_None, REPNOTIFY_Always);
}

void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health, OldValue);
}

void URPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth, OldValue);
}

void URPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Mana, OldValue);
}

void URPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxMana, OldValue);
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);
	UE_LOG(LogTemp, Warning, TEXT("GE生效： %s"), *Data.EvaluatedData.Attribute.GetName());
	ARPGCharacterBase* TargetCharater = nullptr;
	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetCharater = Cast<ARPGCharacterBase>(TargetActor);
	}
	if(TargetCharater != nullptr)
	{
		if (Data.EvaluatedData.Attribute == GetHealthAttribute())
		{
			TargetCharater->OnHealthChanged();
		}
		if (Data.EvaluatedData.Attribute == GetManaAttribute())
		{
			TargetCharater->OnManaChanged();
		}
	}
}

void URPGAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Strength, OldValue);
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	UE_LOG(LogTemp, Warning, TEXT("GE生效： %f"), NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}
