// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RockMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	RockMovement->InitialSpeed = 250.0;
	RockMovement->MaxSpeed = 250.0;
	RockMovement->ProjectileGravityScale = 0.0;

	RockRotation = CreateDefaultSubobject<URotatingMovementComponent>(FName("Projectile Rotation"));
	RockRotation->RotationRate = FRotator(0, -90, 0);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("Projectile Collision"));
	SetRootComponent(SphereCollision); 
	SphereCollision->SetSphereRadius(10.0);



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::DestroyProjectile()
{
	FTimerHandle UnUsedHandle;
	GetWorldTimerManager().SetTimer(UnUsedHandle, this, &AProjectile::DestroyOnTimerExpire, 4.0f, false);
}

void AProjectile::DestroyOnTimerExpire()
{
	Destroy();
}

