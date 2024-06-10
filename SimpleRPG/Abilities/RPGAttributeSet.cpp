// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "SimpleRPG/Characters/RPGCharacterBase.h"


URPGAttributeSet::URPGAttributeSet()
	: HPCurrent(100.f)
	, HPBase(100.f)
	, HPAdd(0.f)
	, ATK(10.f)
	, ATKAdd(0.f)
	, DEF(5.f)
	, DEFAdd(0.f)
	, SPD(1.f)
	, SPDAdd(0.f)
	, CriticalRate(0.05f)
	, CriticalDMG(1.5f)
	, MaxEnergy(100.f)
	, EnergyRegen(1.f)
	, LightningDMGBoost(0.f)
	, FireDMGBoost(0.f)
	, PhysicalDMGBoost(0.f)
	, IceDMGBoost(0.f)
	, LightningRESBoost(0.f)
	, FireRESBoost(0.f)
	, PhysicalRESBoost(0.f)
	, IceRESBoost(0.f)
	, IncomeDamage(0.f)
{
}

void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, HPCurrent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, HPBase, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, HPAdd, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, ATK, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, ATKAdd, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, DEF, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, DEFAdd, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, SPD, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, SPDAdd, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CriticalRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CriticalDMG, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, EnergyRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, LightningDMGBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, FireDMGBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, PhysicalDMGBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, IceDMGBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, LightningRESBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, FireRESBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, PhysicalRESBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, IceRESBoost, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, IncomeDamage, COND_None, REPNOTIFY_Always);
}

void URPGAttributeSet::OnRep_HPCurrent(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, HPCurrent, OldValue);
}

void URPGAttributeSet::OnRep_HPBase(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, HPBase, OldValue);
}

void URPGAttributeSet::OnRep_HPAdd(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, HPAdd, OldValue);
}

void URPGAttributeSet::OnRep_ATK(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ATK, OldValue);
}

void URPGAttributeSet::OnRep_ATKAdd(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ATKAdd, OldValue);
}

void URPGAttributeSet::OnRep_DEF(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, DEF, OldValue);
}

void URPGAttributeSet::OnRep_DEFAdd(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, DEFAdd, OldValue);
}

void URPGAttributeSet::OnRep_SPD(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, SPD, OldValue);
}

void URPGAttributeSet::OnRep_SPDAdd(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, SPDAdd, OldValue);
}

void URPGAttributeSet::OnRep_CriticalRate(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CriticalRate, OldValue);
}

void URPGAttributeSet::OnRep_CriticalDMG(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CriticalDMG, OldValue);
}

void URPGAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxEnergy, OldValue);
}

void URPGAttributeSet::OnRep_EnergyRegen(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, EnergyRegen, OldValue);
}

void URPGAttributeSet::OnRep_LightningDMGBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningDMGBoost, OldValue);
}

void URPGAttributeSet::OnRep_FireDMGBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireDMGBoost, OldValue);
}

void URPGAttributeSet::OnRep_PhysicalDMGBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalDMGBoost, OldValue);
}

void URPGAttributeSet::OnRep_IceDMGBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, IceDMGBoost, OldValue);
}

void URPGAttributeSet::OnRep_LightningRESBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, LightningRESBoost, OldValue);
}

void URPGAttributeSet::OnRep_FireRESBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, FireRESBoost, OldValue);
}

void URPGAttributeSet::OnRep_PhysicalRESBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, PhysicalRESBoost, OldValue);
}

void URPGAttributeSet::OnRep_IceRESBoost(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, IceRESBoost, OldValue);
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	UE_LOG(LogTemp, Warning, TEXT("PostGameplayEffectExecute GE生效： %s"), *Data.EvaluatedData.Attribute.GetName());
	ARPGCharacterBase* TargetCharater = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		AActor* TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetCharater = Cast<ARPGCharacterBase>(TargetActor);
	}
	if (TargetCharater != nullptr)
	{
		if (Data.EvaluatedData.Attribute == GetHPCurrentAttribute())
		{
			TargetCharater->OnHealthChanged();
		}
	}
}

void URPGAttributeSet::OnRep_IncomeDamage(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, IncomeDamage, OldValue);
}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHPCurrentAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetHPBase()+GetHPAdd());
		UE_LOG(LogTemp, Warning, TEXT("PreAttributeChange GE生效： %f"), NewValue);
		AActor* TargetActor = GetActorInfo()->OwnerActor.Get();
		ARPGCharacterBase* TargetCharater = Cast<ARPGCharacterBase>(TargetActor);
		if (TargetCharater)
		{
			if (NewValue <= 0)
			{
				TargetCharater->OnDie();
			}
		}
	}
	Super::PreAttributeChange(Attribute, NewValue);
}
