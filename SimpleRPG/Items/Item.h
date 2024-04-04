// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SimpleRPG/RPGAssetManager.h"
#include "SimpleRPG/RPGInteractInterface.h"
#include "SimpleRPG/Datas/ItemData.h"
#include "Item.generated.h"

// 可拾取物
UCLASS()
class SIMPLERPG_API AItem : public AActor, public IRPGInteractInterface
{
	GENERATED_BODY()
	
public:	
	AItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UItemData* ItemData;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	USphereComponent* Sphere;

	virtual void OnInteract() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;
};
