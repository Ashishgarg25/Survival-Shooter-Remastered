// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "ZomBear.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSHOOTER_API AZomBear : public AEnemyAI
{
	GENERATED_BODY()

public:

	AZomBear();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* EnemyDeathAudio1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* EnemyShotAudio1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* EnemyDeathAudioCue1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* EnemyShotAudioCue1;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHp1();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float UpdateHp1(float HpTaken);

	UFUNCTION()
		void OnEnemyOverlap1(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
