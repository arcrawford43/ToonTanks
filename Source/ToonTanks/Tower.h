// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction() override;
protected:
	virtual void BeginPlay() override;

private:
	void CheckFireCondition();
	bool InFireRange();

	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, category = "Combat")
	float FireRange = 300;

	UPROPERTY(EditDefaultsOnly, category = "Combat")
		float FireRate = 2;

	float FireRangeSquared;

	FTimerHandle FireRateTimerHandle;

};
