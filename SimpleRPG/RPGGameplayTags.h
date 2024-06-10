// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  RPGGameplayTags
 *  Singleton class for native gameplay tags
 */

struct FRPGGameplayTags
{
public:
	static const FRPGGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_BaseStats_HPCurrent;
	FGameplayTag Attributes_BaseStats_HPBase;
	FGameplayTag Attributes_BaseStats_HPAdd;
	FGameplayTag Attributes_BaseStats_ATK;
	FGameplayTag Attributes_BaseStats_ATKAdd;
	FGameplayTag Attributes_BaseStats_DEF;
	FGameplayTag Attributes_BaseStats_DEFAdd;
	FGameplayTag Attributes_BaseStats_SPD;
	FGameplayTag Attributes_BaseStats_SPDAdd;
	
	FGameplayTag Attributes_AdvancedStats_CriticalRate;
	FGameplayTag Attributes_AdvancedStats_CriticalDMG;
	FGameplayTag Attributes_AdvancedStats_MaxEnergy;
	FGameplayTag Attributes_AdvancedStats_EnergyRegen;

	FGameplayTag Attributes_DMGType_LightningDMGBoost;
	FGameplayTag Attributes_DMGType_FireDMGBoost;
	FGameplayTag Attributes_DMGType_PhysicalDMGBoost;
	FGameplayTag Attributes_DMGType_IceDMGBoost;
	FGameplayTag Attributes_DMGType_LightningRESBoost;
	FGameplayTag Attributes_DMGType_FireRESBoost;
	FGameplayTag Attributes_DMGType_PhysicalRESBoost;
	FGameplayTag Attributes_DMGType_IceRESBoost;

	FGameplayTag Attributes_IncomeDamage;

protected:
	
private:
	static FRPGGameplayTags GameplayTags;
};
