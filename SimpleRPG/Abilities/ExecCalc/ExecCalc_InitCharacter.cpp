// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecCalc_InitCharacter.h"
#include "AbilitySystemComponent.h"
#include "SimpleRPG/Abilities/RPGAttributeSet.h"

struct RPGInitCharacterStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(HPCurrent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DEF);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ATK);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SPD);
	
	
	RPGInitCharacterStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, HPCurrent, Source, true)
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DEF, Source, true)
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ATK, Source, true)
	}
};

static const RPGInitCharacterStatics& InitCharacterStatics()
{
	static RPGInitCharacterStatics InitCharacterStatics;
	return InitCharacterStatics;
}

UExecCalc_InitCharacter::UExecCalc_InitCharacter()
{
	RelevantAttributesToCapture.Add(InitCharacterStatics().ATKDef);
	RelevantAttributesToCapture.Add(InitCharacterStatics().DEFDef);
}

void UExecCalc_InitCharacter::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float ATK = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ATKDef, EvaluationParameters, ATK);
	float DEF = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DEFDef, EvaluationParameters, DEF);
	float Damage = FMath::Max(ATK - DEF, 0.f);
	const FGameplayModifierEvaluatedData EvaluatedData(DamageStatics().HPCurrentProperty, EGameplayModOp::Additive, -Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
