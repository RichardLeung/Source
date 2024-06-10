// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RPGAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class SIMPLERPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URPGAttributeSet();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadOnly, Category="当前属性 - 当前生命值")
	FGameplayAttributeData HPCurrent;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HPCurrent);
	UFUNCTION()
	void OnRep_HPCurrent(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category="基础属性 - 基础生命值")
	FGameplayAttributeData HPBase;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HPBase);
	UFUNCTION()
	void OnRep_HPBase(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 生命值增加")
	FGameplayAttributeData HPAdd;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HPAdd);
	UFUNCTION()
	void OnRep_HPAdd(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 攻击力")
	FGameplayAttributeData ATK;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ATK);
	UFUNCTION()
	void OnRep_ATK(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 攻击力增加")
	FGameplayAttributeData ATKAdd;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ATKAdd);
	UFUNCTION()
	void OnRep_ATKAdd(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 防御力")
	FGameplayAttributeData DEF;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, DEF);
	UFUNCTION()
	void OnRep_DEF(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 防御力增加")
	FGameplayAttributeData DEFAdd;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, DEFAdd);
	UFUNCTION()
	void OnRep_DEFAdd(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 速度")
	FGameplayAttributeData SPD;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SPD);
	UFUNCTION()
	void OnRep_SPD(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "基础属性 - 速度增加")
	FGameplayAttributeData SPDAdd;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, SPDAdd);
	UFUNCTION()
	void OnRep_SPDAdd(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "高级属性 - 暴击率")
	FGameplayAttributeData CriticalRate;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalRate);
	UFUNCTION()
	void OnRep_CriticalRate(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "高级属性 - 暴击伤害")
	FGameplayAttributeData CriticalDMG;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalDMG);
	UFUNCTION()
	void OnRep_CriticalDMG(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "高级属性 - 最大能量")
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxEnergy);
	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "高级属性 - 能量恢复")
	FGameplayAttributeData EnergyRegen;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, EnergyRegen);
	UFUNCTION()
	void OnRep_EnergyRegen(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 闪电伤害提升")
	FGameplayAttributeData LightningDMGBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, LightningDMGBoost);
	UFUNCTION()
	void OnRep_LightningDMGBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 火焰伤害提升")
	FGameplayAttributeData FireDMGBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireDMGBoost);
	UFUNCTION()
	void OnRep_FireDMGBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 物理伤害提升")
	FGameplayAttributeData PhysicalDMGBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalDMGBoost);
	UFUNCTION()
	void OnRep_PhysicalDMGBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 冰霜伤害提升")
	FGameplayAttributeData IceDMGBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, IceDMGBoost);
	UFUNCTION()
	void OnRep_IceDMGBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 闪电抗性提升")
	FGameplayAttributeData LightningRESBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, LightningRESBoost);
	UFUNCTION()
	void OnRep_LightningRESBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 火焰抗性提升")
	FGameplayAttributeData FireRESBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireRESBoost);
	UFUNCTION()
	void OnRep_FireRESBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 物理抗性提升")
	FGameplayAttributeData PhysicalRESBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalRESBoost);
	UFUNCTION()
	void OnRep_PhysicalRESBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "伤害类型 - 冰霜抗性提升")
	FGameplayAttributeData IceRESBoost;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, IceRESBoost);
	UFUNCTION()
	void OnRep_IceRESBoost(const FGameplayAttributeData& OldValue) const;

	UPROPERTY(BlueprintReadOnly, Category = "收到伤害")
	FGameplayAttributeData IncomeDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, IncomeDamage);
	UFUNCTION()
	void OnRep_IncomeDamage(const FGameplayAttributeData& OldValue) const;
	
	// 属性修改前回调
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// GE执行后属性回调
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
};
