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
	static const FRPGGameplayTags& Get() { return GameplayTagsInstance; }
	static void InitializeNativeGameplayTags();
protected:
	
private:
	static FRPGGameplayTags GameplayTagsInstance;
};
