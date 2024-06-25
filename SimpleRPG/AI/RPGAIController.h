// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/AIController.h"
#include "RPGAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class SIMPLERPG_API ARPGAIController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARPGAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	
};
