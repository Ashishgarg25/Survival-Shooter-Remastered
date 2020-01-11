// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon mesh"));
	WeaponMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::SpawnProjectiles()
{
	FHitResult OutHit;
	
	FVector Start = WeaponMesh->GetSocketLocation("MuzzleSocket");

	FVector End = Start + (GetActorForwardVector() * 2000.f);

	GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECollisionChannel::ECC_Visibility);

	//if (OutHit.bBlockingHit)
	//{
		FRotator rot = GetActorRotation();

		FActorSpawnParameters SpawnParams;

		GetWorld()->SpawnActor(Bullet, &Start, &rot, SpawnParams);

		UE_LOG(LogTemp, Warning, TEXT("Bullet Spawning"));
	//}
}
