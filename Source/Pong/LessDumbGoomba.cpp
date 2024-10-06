// Fill out your copyright notice in the Description page of Project Settings.


#include "LessDumbGoomba.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"

void ALessDumbGoomba::BeginPlay()
{
	Super::BeginPlay();

	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALessDumbGoomba::OnLeftOverlap);
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALessDumbGoomba::OnRightOverlap);
}

void ALessDumbGoomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyBodyCollider->AddForce(FVector(WalkingDirection, 0, 0) * EnemyHorizontalAcceleration);

	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -EnemyMaxSpeed, EnemyMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
}

void ALessDumbGoomba::OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = 1;
	}
}

void ALessDumbGoomba::OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Tags.Contains("Floor"))
	{
		WalkingDirection = -1;
	}
}