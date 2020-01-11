// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyAI.h"
#include "Hellephant.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSHOOTER_API AHellephant : public AEnemyAI
{
	GENERATED_BODY()
	
public:

	AHellephant();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* EnemyDeathAudio2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAudioComponent* EnemyShotAudio2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* EnemyDeathAudioCue2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USoundCue* EnemyShotAudioCue2;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHp2();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float UpdateHp2(float HpTaken);

	UFUNCTION()
		void OnEnemyOverlap2(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
