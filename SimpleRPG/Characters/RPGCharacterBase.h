// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleRPG/Interfaces/CombatInterface.h"
#include "RPGCharacterBase.generated.h"

UCLASS()
class SIMPLERPG_API ARPGCharacterBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacterBase();

	// 角色名称
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	FName CharacterName;

	// 角色等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	int32 Level;

	// 角色突破等级
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	int32 BreakLevel;

	// 角色经验
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "角色|基础属性")
	UDataTable* DT_AttributeInfo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FVector GetCombatProjectileLocation() override;
};
