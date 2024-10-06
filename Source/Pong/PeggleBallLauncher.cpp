// Fill out your copyright notice in the Description page of Project Settings.


#include "PeggleBallLauncher.h"
#include <PaperSpriteActor.h>
#include "PaperSpriteComponent.h"

// Sets default values
APeggleBallLauncher::APeggleBallLauncher()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

bool APeggleBallLauncher::GetReadyToFire()
{
	return ReadyToFire;
}

void APeggleBallLauncher::SetReadyToFire(bool ready_bool)
{
	ReadyToFire = ready_bool;
}

bool APeggleBallLauncher::GetMultiballActive()
{
	return MultiballActive;
}

void APeggleBallLauncher::SetMultiballActive(bool ready_bool)
{
	MultiballActive = ready_bool;
}

bool APeggleBallLauncher::GetSpookyActive()
{
	return SpookyActive;
}

void APeggleBallLauncher::SetSpookyActive(bool ready_bool)
{
	SpookyActive = ready_bool;
}

// Called when the game starts or when spawned
void APeggleBallLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

void APeggleBallLauncher::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	MySprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MySprite->TranslucencySortPriority = 3;
}

// Called every frame
void APeggleBallLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 // Called to bind functionality to input
void APeggleBallLauncher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Horizontal", this, &APeggleBallLauncher::MovePlayer);
	InputComponent->BindAction("Fire", IE_Pressed, this, &APeggleBallLauncher::Fire);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APeggleBallLauncher::MovePlayer(float input)
{
	SetActorRotation(GetActorRotation() + FRotator(1 * input, 0, 0));
}

void APeggleBallLauncher::Fire()
{
	if (ReadyToFire == 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Firing!"));
		AActor* SpawnedBall = GetWorld()->SpawnActor<AActor>(BallBPClass, GetActorLocation(), GetActorRotation());
		FVector ShotDirection = GetActorUpVector() *= -1;
		SpawnedBall->GetComponentByClass<UPaperSpriteComponent>()->AddImpulse(ShotDirection * ShotPower);

		if (MultiballActive == 1)
		{
			AActor* MultiBall = GetWorld()->SpawnActor<AActor>(BallBPClass, GetActorLocation(), GetActorRotation());
			MultiBall->GetComponentByClass<UPaperSpriteComponent>()->AddImpulse(ShotDirection * ShotPower);
			MultiballActive = 0;
		}

		ReadyToFire = 0;
	}
}

