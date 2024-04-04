// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleRPG/Datas/BaseItemData.h"
#include "RPGShopComponent.generated.h"


USTRUCT(BlueprintType)
struct FShopItemInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	FDataTableRowHandle ItemData;

	// 道具数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 ItemCount;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLERPG_API URPGShopComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URPGShopComponent();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	TArray<FShopItemInfo> GetShopItems() const
	{
		return AvailableItems;
	};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// 商店中可以卖的道具及数量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop", meta = (AllowPrivateAccess = "true"))
	TArray<FShopItemInfo> AvailableItems;
};
