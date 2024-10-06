// Fill out your copyright notice in the Description page of Project Settings.


#include "Goomba.h"
#include "Mario.h"
#include <PaperFlipbookComponent.h>
#include <Engine.h>

// Sets default values
AGoomba::AGoomba()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Goomba Body Sprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("My Body"));
	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Detector"));
	LeftTrigger->SetBoxExtent(FVector(32, 32, 32));
	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Right Detector"));
	RightTrigger->SetBoxExtent(FVector(32, 32, 32));
	HeadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Body Detector"));
	HeadTrigger->SetBoxExtent(FVector(32, 32, 32));

	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	LeftTrigger->SetupAttachment(RootComponent);
	RightTrigger->SetupAttachment(RootComponent);
	HeadTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGoomba::BeginPlay()
{
	Super::BeginPlay();
	MyBodyCollider->OnComponentHit.AddDynamic(this, &AGoomba::OnCollision);
	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGoomba::OnHeadOverlap);
	ProcessAnimStateMachine();
}

void AGoomba::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		Destroy();
	}
}

void AGoomba::IdentifyAnimStates()
{
	OldAnimationState = CurrentAnimationState;

	float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().X;
	if (CurrentSpeed > 5)
	{
		CurrentAnimationState = SkeletonAnimationState::AS_WALKING_RIGHT;
	}
	else if (CurrentSpeed < -5)
	{
		CurrentAnimationState = SkeletonAnimationState::AS_WALKING_LEFT;
	}
	else
	{
		CurrentAnimationState = SkeletonAnimationState::AS_IDLE;
	}
}

void AGoomba::ProcessAnimStateMachine()
{
	if (CurrentAnimationState == OldAnimationState)
	{
		return;
	}

	switch (CurrentAnimationState)
	{
	case SkeletonAnimationState::AS_IDLE:
	{
		MySprite->SetFlipbook(Flipbook_Idle);
		break;
	}
	case SkeletonAnimationState::AS_WALKING_RIGHT:
	{
		MySprite->SetFlipbook(Flipbook_WalkingRight);
		MySprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		break;
	}
	case SkeletonAnimationState::AS_WALKING_LEFT:
	{
		MySprite->SetFlipbook(Flipbook_WalkingRight);
		MySprite->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
		break;
	}
	case SkeletonAnimationState::AS_DEAD:
	{
		MySprite->SetFlipbook(Flipbook_Death);
	}
	}
}

// Called every frame
void AGoomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IdentifyAnimStates();
	ProcessAnimStateMachine();
}

// Called to bind functionality to input
void AGoomba::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario();
	}

}

void AGoomba::KillGoomba()
{
	Destroy();
}

