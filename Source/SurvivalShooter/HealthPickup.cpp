// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "SurvivalShooterCharacter.h"
#include "Engine.h"

// Sets default values
AHealthPickup::AHealthPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HpPickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));
	HpPickupMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	HpPickupCollsionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Component"));
	HpPickupCollsionComp->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	HpPickupCollsionComp->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickup::OnPickup);
	HpPickupCollsionComp->SetupAttachment(HpPickupMesh);
}

void AHealthPickup::OnPickup(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ASurvivalShooterCharacter* Player = (ASurvivalShooterCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);
		
		if (OtherActor == Player) {
			UE_LOG(LogTemp, Warning, TEXT("HP PICKED UP"));

			float HpVal = FMath::RandRange(50.f, 70.f);

			Player->CurrentHp += HpVal;

			if (Player->CurrentHp >= Player->MaxHp) {
				Player->CurrentHp = Player->MaxHp;
			}

			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AHealthPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

