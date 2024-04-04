// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "URPGSkill.generated.h"

class UGameplayAbility;

/**
 * 
 */
UCLASS()
class SIMPLERPG_API UURPGSkill : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	class UTexture2D* SkillIcon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	TSubclassOf<UGameplayAbility> GameplayAbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float CooldownDuration;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(FPrimaryAssetType(TEXT("Skill")), GetFName());
	}
};
