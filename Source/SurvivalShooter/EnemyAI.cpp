// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAI.h"
#include "SurvivalShooterCharacter.h"
#include "Engine.h"
#include "SurvivalShooterGameMode.h"
#include "Components/AudioComponent.h"

// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAI::OnEnemyOverlap);

	EnemyShotAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("EnemyShot Audio"));

	EnemyDeathAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("EnemyDeath Audio"));
}

float AEnemyAI::GetCurrentHp()
{
	return (CurrentHp / MaxHp);
}

float AEnemyAI::UpdateHp(float HpTaken)
{
	CurrentHp -= HpTaken;

	if (CurrentHp >= MaxHp) {
		CurrentHp = MaxHp;
	}
	else if (CurrentHp < MaxHp)
	{
		EnemyShotAudio->SetSound(EnemyShotAudioCue);
		EnemyShotAudio->Play();
		
		if (CurrentHp <= 0.0f) {

			UE_LOG(LogTemp, Warning, TEXT("No ZomBunny HP"));

			EnemyDeathAudio->SetSound(EnemyDeathAudioCue);
			EnemyDeathAudio->Play();

			FTransform trans = GetActorTransform();
			FActorSpawnParameters SpawnParams;

			GetWorld()->SpawnActor(HpDrop, &trans, SpawnParams);

			ASurvivalShooterGameMode* GameMode = (ASurvivalShooterGameMode*)GetWorld()->GetAuthGameMode();
			GameMode->ScoreCount(5);

			Destroy();
		}
	}

	return CurrentHp;
}


void AEnemyAI::OnEnemyOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResults)
{
	if (OverlappedComp != NULL && OtherComp != NULL && OtherActor != this)
	{
		ASurvivalShooterCharacter* Player = (ASurvivalShooterCharacter*)UGameplayStatics::GetPlayerCharacter(this, 0);

		if (OtherActor == Player) {
			float Damage = FMath::RandRange(50, 100);
			Player->UpdateHp(Damage);
			UE_LOG(LogTemp, Warning, TEXT("IS OVERLAPPING"));
		}

		else if (OtherActor->ActorHasTag("Bullet")) {
			float Dmg = FMath::RandRange(100, 150);
			UpdateHp(Dmg);

			OtherActor->Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
	MaxHp = 500.f;
	CurrentHp = MaxHp;
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

