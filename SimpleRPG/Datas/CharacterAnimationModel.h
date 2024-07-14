// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterAnimationModel.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLERPG_API UCharacterAnimationModel : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	// 基本运动动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|基本")
	TSoftObjectPtr<UAnimSequence> IdleAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|基本")
	TSoftObjectPtr<UAnimSequence> WalkAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|基本")
	TSoftObjectPtr<UAnimSequence> RunAnimation;

	// 战斗动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|战斗")
	TSoftObjectPtr<UAnimSequence> AttackAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|战斗")
	TSoftObjectPtr<UAnimSequence> SkillAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|战斗")
	TSoftObjectPtr<UAnimSequence> UltimateAnimation;

	// 受伤和死亡动画
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|战斗")
	TSoftObjectPtr<UAnimSequence> HitReactionAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "动画|战斗")
	TSoftObjectPtr<UAnimSequence> DeathAnimation;
	
};
