// Fill out your copyright notice in the Description page of Project Settings.


#include "SpringPad.h"
#include "Mario.h"
#include <PaperSpriteComponent.h>
#include <PaperFlipbookComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
ASpringPad::ASpringPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Spring Sprite"));

	SpringBoard = CreateDefaultSubobject<UBoxComponent>(TEXT("Unbreakable Box"));
	SpringBoard->SetBoxExtent(FVector(32, 32, 32));
	SpringBody = CreateDefaultSubobject<UBoxComponent>(TEXT("Breakable Box"));
	SpringBody->SetBoxExtent(FVector(32, 32, 32));

	RootComponent = MySprite;
	SpringBoard->SetupAttachment(RootComponent);
	SpringBody->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASpringPad::BeginPlay()
{
	Super::BeginPlay();


	SpringBoard->OnComponentBeginOverlap.AddDynamic(this, &ASpringPad::OnOverlap);
	ProcessAnimStateMachine();
	ResetSpring();
	
}

// Called every frame
void ASpringPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IdentifyAnimStates();
	ProcessAnimStateMachine();
	if (SpringSprung)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpringSprung is true"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpringSprung is false"));
	}
}

void ASpringPad::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMario::StaticClass()) && (SpringSprung == false))
	{
		UE_LOG(LogTemp, Warning, TEXT("BOUNCE"));
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		SpringSprung = true;
		GetWorld()->GetTimerManager().SetTimer(SpringTimer, this, &ASpringPad::ResetSpring, 0.1, false);

	}

}

void ASpringPad::IdentifyAnimStates()
{
	OldAnimationState = CurrentAnimationState;

	if (SpringSprung == false)
	{
		CurrentAnimationState = SpringAnimationState::AS_READY;
	}
	else if (SpringSprung == true)
	{
		CurrentAnimationState = SpringAnimationState::AS_SPRUNG;
	}
}

void ASpringPad::ProcessAnimStateMachine()
{
	if (CurrentAnimationState == OldAnimationState)
	{
		return;
	}

	switch (CurrentAnimationState)
	{
	case SpringAnimationState::AS_READY:
		{
			MySprite->SetFlipbook(Flipbook_Ready);
			break;
		}
	case SpringAnimationState::AS_SPRUNG:
		{
			MySprite->SetFlipbook(Flipbook_Sprung);
			MySprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
			break;
		}
	}
}

void ASpringPad::ResetSpring()
{
	SpringSprung = false;
}

