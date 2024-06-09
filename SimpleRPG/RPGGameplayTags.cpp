// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayTags.h"
#include "GameplayTagsManager.h"

FRPGGameplayTags FRPGGameplayTags::GameplayTagsInstance;

void FRPGGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Health"), FString("Attribute.Health"));
}
