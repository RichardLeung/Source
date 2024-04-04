// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Components/BoxComponent.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class UWeaponData;

/**
 * 角色装备的武器
 */
UCLASS()
class SIMPLERPG_API AWeapon : public AActor
{
	GENERATED_BODY()

public:

	AWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UWeaponData* WeaponData;

	void InitWeapon(UWeaponData* ItemData);

	void Equip(USceneComponent* InParent, FName InSocketName);

	void SetEnableCollision(ECollisionEnabled::Type NewCollisionEnabled);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	UBoxComponent* WeaponBox;
	
	UPROPERTY(VisibleAnywhere, Category="Weapon")
	USoundBase* EquipSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	USceneComponent* BoxTraceStart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
	USceneComponent* BoxTraceEnd;

	TArray<AActor*> IgnoreActors;

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

