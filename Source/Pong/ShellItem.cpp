// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellItem.h"
#include "Mario.h"
#include "Goomba.h"
#include <PaperFlipbookComponent.h>
#include "Components/BoxComponent.h"

// Sets default values
AShellItem::AShellItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isMoving = false;
	speed = 10.0;
	direction = FVector(0, 0, 0);

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Shell Body Sprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("My Body"));
	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Detector"));
	LeftTrigger->SetBoxExtent(FVector(32, 32, 32));
	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Right Detector"));
	RightTrigger->SetBoxExtent(FVector(32, 32, 32));
	HeadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Head Detector"));
	HeadTrigger->SetBoxExtent(FVector(32, 32, 32));
	
	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	LeftTrigger->SetupAttachment(RootComponent);
	RightTrigger->SetupAttachment(RootComponent);
	HeadTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShellItem::BeginPlay()
{
	Super::BeginPlay();

	LeftTrigger->OnComponentBeginOverlap.AddDynamic(this, &AShellItem::OnLeftOverlap);
	RightTrigger->OnComponentBeginOverlap.AddDynamic(this, &AShellItem::OnRightOverlap);
	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &AShellItem::OnHeadOverlap);
	
}

// Called every frame
void AShellItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);

	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -ShellMaxSpeed, ShellMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);

}

void AShellItem::OnLeftOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("IsMoving: %s"), isMoving ? TEXT("True") : TEXT("False"));

	direction = FVector(1, 0, 0);

	if (!isMoving)
	{
		isMoving = true;
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}

	else if (OtherActor->IsA(AMario::StaticClass()) && isMoving == true)
	{
		Cast<AMario>(OtherActor)->KillMario();
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}
	else if (OtherActor->IsA(AGoomba::StaticClass()) && isMoving == true)
	{
		Cast<AGoomba>(OtherActor)->KillGoomba();
		Destroy();
	}
	else if (OtherActor->Tags.Contains("Floor"))
	{
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}

	else
	{
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}
}

void AShellItem::OnRightOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherCmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("IsMoving: %s"), isMoving ? TEXT("True") : TEXT("False"));
	direction = FVector(-1, 0, 0);
	if (!isMoving)
	{
		isMoving = true;
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);

		FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
		ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -ShellMaxSpeed, ShellMaxSpeed);
		MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
	}

	else if (OtherActor->IsA(AMario::StaticClass()) && isMoving == true)
	{
		Cast<AMario>(OtherActor)->KillMario();
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}
	else if (OtherActor->IsA(AGoomba::StaticClass()) && isMoving == true)
	{
		Cast<AGoomba>(OtherActor)->KillGoomba();
		Destroy();
	}
	else if (OtherActor->Tags.Contains("Floor"))
	{
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}

	else
	{
		MyBodyCollider->AddForce(FVector(direction) * ShellHorizontalAcceleration);
	}
}

void AShellItem::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Head overlap triggered"));
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		isMoving = false;
		direction = FVector(0, 0, 0);
	}
}