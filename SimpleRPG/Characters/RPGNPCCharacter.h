// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "SimpleRPG/RPGInteractInterface.h"
#include "SimpleRPG/Datas/CharacterData.h"
#include "RPGNPCCharacter.generated.h"

class UItemData;

UCLASS()
class SIMPLERPG_API ARPGNPCCharacter : public ACharacter, public IRPGInteractInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGNPCCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	FDataTableRowHandle CharacterDataTableRowHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "NPC")
	FCharacterData CharacterData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="NPC")
	UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NPC")
	float ShowRange = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NPC")
	float InteractRange = 300.f;
	
protected:
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnInteract() override;

	UFUNCTION(BlueprintImplementableEvent)
	void k2_OnInteract();

private:
	UPROPERTY()
	class ARPGCharacterBase* PlayerCharacter;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* Sphere;
	
	UFUNCTION()
	bool InShowRange();

	
};
