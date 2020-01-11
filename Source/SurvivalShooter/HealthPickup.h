// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickup.generated.h"

UCLASS()
class SURVIVALSHOOTER_API AHealthPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* HpPickupMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* HpPickupCollsionComp;

	UFUNCTION()
		void OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
