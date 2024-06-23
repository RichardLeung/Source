// Fill out your copyright notice in the Description page of Project Settings.


#include "ExecCalc_InitCharacter.h"
#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleRPG/RPGGameInstanceBase.h"
#include "SimpleRPG/Abilities/RPGAttributeSet.h"
#include "SimpleRPG/Characters/RPGCharacterBase.h"

struct RPGInitCharacterStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(HPBase);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HPCurrent);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DEF);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ATK);
	
	RPGInitCharacterStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, HPBase, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, HPCurrent, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, DEF, Source, false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(URPGAttributeSet, ATK, Source, false)
	}
};

static const RPGInitCharacterStatics& InitCharacterStatics()
{
	static RPGInitCharacterStatics InitCharacterStatics;
	return InitCharacterStatics;
}

UExecCalc_InitCharacter::UExecCalc_InitCharacter()
{
	RelevantAttributesToCapture.Add(InitCharacterStatics().HPBaseDef);
	RelevantAttributesToCapture.Add(InitCharacterStatics().HPCurrentDef);
	RelevantAttributesToCapture.Add(InitCharacterStatics().ATKDef);
	RelevantAttributesToCapture.Add(InitCharacterStatics().DEFDef);
}

void UExecCalc_InitCharacter::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UE_LOG(LogTemp, Warning, TEXT("开始角色初始化"));
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
	// ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(RPGInitCharacterStatics().ATKDef, EvaluationParameters, Level);
	const ARPGCharacterBase* SourceCharacter = Cast<ARPGCharacterBase>(SourceActor);
	if (!SourceCharacter)
	{
		return;
	}
	UDataTable* DT_AttributeInfo = SourceCharacter->DT_AttributeInfo;
	if (!DT_AttributeInfo)
	{
		return;
	}
	FCharacterLevelAttributeInfo* AttributeInfoData = DT_AttributeInfo->FindRow<FCharacterLevelAttributeInfo>(FName(*FString::FromInt(SourceCharacter->Level+100*SourceCharacter->BreakLevel)), FString(""));
	if (!AttributeInfoData)
	{
		return;
	}
	const FGameplayModifierEvaluatedData EvaluatedData(RPGInitCharacterStatics().HPCurrentProperty, EGameplayModOp::Override, AttributeInfoData->HPBase);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	const FGameplayModifierEvaluatedData EvaluatedData2(RPGInitCharacterStatics().HPBaseProperty, EGameplayModOp::Override, AttributeInfoData->HPBase);
	OutExecutionOutput.AddOutputModifier(EvaluatedData2);
	const FGameplayModifierEvaluatedData EvaluatedData3(RPGInitCharacterStatics().DEFProperty, EGameplayModOp::Override, AttributeInfoData->DEF);
	OutExecutionOutput.AddOutputModifier(EvaluatedData3);
	const FGameplayModifierEvaluatedData EvaluatedData4(RPGInitCharacterStatics().ATKProperty, EGameplayModOp::Override, AttributeInfoData->ATK);
	OutExecutionOutput.AddOutputModifier(EvaluatedData4);
	UE_LOG(LogTemp, Warning, TEXT("结束角色初始化"));
}
