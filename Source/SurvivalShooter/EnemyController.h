// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALSHOOTER_API AEnemyController : public AAIController
{
	GENERATED_BODY()
	
public:

	AEnemyController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightRadius = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AISightAge = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AILoseSightRadius = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		float AIFieldOfView = 90.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		class UAISenseConfig_Sight* SightConfig;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void OnPossess(APawn* Pawn) override;

	virtual FRotator GetControlRotation() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DistanceToPlayer = 0.0f;

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*> &DetectedPawn);

};
