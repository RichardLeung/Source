// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayTags.h"
#include "GameplayTagsManager.h"

FRPGGameplayTags FRPGGameplayTags::GameplayTags;

void FRPGGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_BaseStats_HPCurrent = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.HPCurrent"),
		FString("基础属性 - 当前生命值"));
	GameplayTags.Attributes_BaseStats_HPBase = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.HPBase"),
		FString("基础属性 - 基础生命值"));
	GameplayTags.Attributes_BaseStats_HPAdd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.HPAdd"),
		FString("基础属性 - 生命值加成"));
	GameplayTags.Attributes_BaseStats_ATK = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.ATK"),
		FString("基础属性 - 基础攻击力"));
	GameplayTags.Attributes_BaseStats_ATKAdd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.ATKAdd"),
		FString("基础属性 - 攻击力加成"));
	GameplayTags.Attributes_BaseStats_DEF = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.DEF"),
		FString("基础属性 - 基础防御力"));
	GameplayTags.Attributes_BaseStats_DEFAdd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.DEFAdd"),
		FString("基础属性 - 防御力加成"));
	GameplayTags.Attributes_BaseStats_SPD = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SPD"),
		FString("基础属性 - 速度"));
	GameplayTags.Attributes_BaseStats_SPDAdd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.SPDAdd"),
		FString("基础属性 - 速度加成"));
	GameplayTags.Attributes_AdvancedStats_CriticalRate = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CriticalRate"),
		FString("高级属性 - 暴击率"));

	GameplayTags.Attributes_AdvancedStats_CriticalDMG = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.CriticalDMG"),
		FString("高级属性 - 暴击伤害"));

	GameplayTags.Attributes_AdvancedStats_MaxEnergy = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.MaxEnergy"),
		FString("高级属性 - 最大能量"));

	GameplayTags.Attributes_AdvancedStats_EnergyRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.EnergyRegen"),
		FString("高级属性 - 能量恢复"));

	GameplayTags.Attributes_DMGType_LightningDMGBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.LightningDMGBoost"),
		FString("伤害类型 - 闪电伤害提升"));

	GameplayTags.Attributes_DMGType_FireDMGBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.FireDMGBoost"),
		FString("伤害类型 - 火焰伤害提升"));

	GameplayTags.Attributes_DMGType_PhysicalDMGBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PhysicalDMGBoost"),
		FString("伤害类型 - 物理伤害提升"));

	GameplayTags.Attributes_DMGType_IceDMGBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.IceDMGBoost"),
		FString("伤害类型 - 冰霜伤害提升"));

	GameplayTags.Attributes_DMGType_LightningRESBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.LightningRESBoost"),
		FString("伤害类型 - 闪电抗性提升"));

	GameplayTags.Attributes_DMGType_FireRESBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.FireRESBoost"),
		FString("伤害类型 - 火焰抗性提升"));

	GameplayTags.Attributes_DMGType_PhysicalRESBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.PhysicalRESBoost"),
		FString("伤害类型 - 物理抗性提升"));

	GameplayTags.Attributes_DMGType_IceRESBoost = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.IceRESBoost"),
		FString("伤害类型 - 冰霜抗性提升"));

	GameplayTags.Attributes_IncomeDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.IncomeDamage"),
		FString("收到伤害"));
}
