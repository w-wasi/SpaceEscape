// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileShooter.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"


// Sets default values
AProjectileShooter::AProjectileShooter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileSpawner = CreateDefaultSubobject<UStaticMeshComponent>(FName("Projectile Spawner"));
	SetRootComponent(ProjectileSpawner);
	ProjectileSpawner->SetHiddenInGame(true);

	SpawnPositionTop = CreateDefaultSubobject<USceneComponent>(FName("Projectile Top Ref"));
	SpawnPositionTop->SetupAttachment(RootComponent);
	SpawnPositionTop->SetRelativeLocation(FVector(-17.0, 8.0, 57.0));

	SpawnPositionBottom = CreateDefaultSubobject<USceneComponent>(FName("Projectile Bottom Ref"));
	SpawnPositionBottom->SetupAttachment(RootComponent);
	SpawnPositionBottom->SetRelativeLocation(FVector(-17.0, 8.0, 0.0));

}

void AProjectileShooter::ShootProjectile()
{
	FTimerHandle UnUsedHandle;
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &AProjectileShooter::SpawnProjectile, 0.5f, true);
}

void AProjectileShooter::SpawnProjectile()
{
	if (!ProjectileBPClass) {
		return;
	}

	auto Choice = FMath::RandRange(MinRange, MaxRange);

	if (bCanShootProjectile) {
	
		AProjectile* RockProjectile = nullptr;

		switch (Choice)
		{
		case 0:
			RockProjectile = SpawnBottom();
			break;
		case 1:
			RockProjectile = SpawnBottom();
			break;
		case 2:
			//SpawnNothing
			break;
		case 3:
			RockProjectile = SpawnTop();
			break;
		case 4:
			RockProjectile = SpawnBottom();
			break;
		default:
			break;
		}

		//destroy here
		if (RockProjectile != nullptr) {
		
			RockProjectile->DestroyProjectile();
		}
	}


	/*
		
	*/
}

AProjectile* AProjectileShooter::SpawnTop()
{
	auto ProjCreated = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBPClass,
		SpawnPositionTop->GetComponentLocation(),
		SpawnPositionTop->GetComponentRotation()
		);

	LastSpawnTime = FPlatformTime::Seconds();
	NextSpawnTime = FMath::RandRange(0.5f, 2.5f);

	return ProjCreated;
}

AProjectile* AProjectileShooter::SpawnBottom()
{
	auto ProjCreated = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBPClass,
		SpawnPositionBottom->GetComponentLocation(),
		SpawnPositionBottom->GetComponentRotation()
	);

	LastSpawnTime = FPlatformTime::Seconds();
	NextSpawnTime = FMath::RandRange(0.5f, 2.5f);

	return ProjCreated;
}

// Called when the game starts or when spawned
void AProjectileShooter::BeginPlay()
{
	Super::BeginPlay();
	LastSpawnTime = FPlatformTime::Seconds();
	ShootProjectile();
	
}

// Called every frame
void AProjectileShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeElapsed = FPlatformTime::Seconds() - LastSpawnTime;
	bCanShootProjectile = TimeElapsed > NextSpawnTime;

}

