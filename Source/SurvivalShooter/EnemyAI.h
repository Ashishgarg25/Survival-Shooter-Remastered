// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyAI.generated.h"

UCLASS()
class SURVIVALSHOOTER_API AEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		TSubclassOf <class AActor> HpDrop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float CurrentHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float MaxHp;

	UFUNCTION(BlueprintPure, Category = "Health")
		float GetCurrentHp();

	UFUNCTION(BlueprintCallable, Category = "Health")
		float UpdateHp(float HpTaken);

	UFUNCTION()
		void OnEnemyOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere)
		class UAudioComponent* EnemyDeathAudio;

	UPROPERTY(EditAnywhere)
		class UAudioComponent* EnemyShotAudio;

	UPROPERTY(EditAnywhere)
		class USoundCue* EnemyDeathAudioCue;

	UPROPERTY(EditAnywhere)
		class USoundCue* EnemyShotAudioCue;

};
