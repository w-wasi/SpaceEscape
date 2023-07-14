// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class URotatingMovementComponent;
class USphereComponent;

UCLASS()
class TWODRUNNERCPP_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DestroyOnTimerExpire();

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* RockMovement = nullptr;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RockRotation = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereCollision = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void DestroyProjectile();

};
