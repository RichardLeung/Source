// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAnimInstance.h"
#include "RPGCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void URPGAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	RPGCharacter = Cast<ARPGCharacterBase>(TryGetPawnOwner());
	if (RPGCharacter)
	{
		RPGCharacterMovement = RPGCharacter->GetCharacterMovement();
	}
}

void URPGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (RPGCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(RPGCharacterMovement->Velocity);
		IsFalling = RPGCharacterMovement->IsFalling();
		CharacterState = RPGCharacter->GetCharacterState();
	}
}
