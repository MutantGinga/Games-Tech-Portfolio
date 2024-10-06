// Fill out your copyright notice in the Description page of Project Settings.

#include "Mario.h"
#include "PaperFlipbookComponent.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Engine.h>

void AMario::MovePlayerHorizontal(float input)
{
	MyBodyCollider->AddForce(FVector(1, 0, 0) * input * PlayerAcceleration, NAME_None, false);
}

void AMario::Jump()
{
	/*MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce);*/
	if (!bIsJumping)
	{
		MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce);
		bIsJumping = true;
	}
}

void AMario::IdentifyAnimStates()
{
	OldAnimationState = CurrentAnimationState;

	float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().X;
	if (CurrentSpeed > 1)
	{
		CurrentAnimationState = KnightAnimationState::AS_WALKING_RIGHT;
	}
	else if (CurrentSpeed < -1)
	{
		CurrentAnimationState = KnightAnimationState::AS_WALKING_LEFT;
	}
	else
	{
		CurrentAnimationState = KnightAnimationState::AS_IDLE;
	}
}

void AMario::ProcessAnimStateMachine()
{
	if (CurrentAnimationState == OldAnimationState)
	{
		return;
	}

	switch (CurrentAnimationState)
	{
	case KnightAnimationState::AS_IDLE:
			{
				MySprite->SetFlipbook(Flipbook_Idle);
				break;
			}
	case KnightAnimationState::AS_WALKING_RIGHT:
			{
				MySprite->SetFlipbook(Flipbook_WalkingRight);
				MySprite->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
				break;
			}
	case KnightAnimationState::AS_WALKING_LEFT:
			{
				MySprite->SetFlipbook(Flipbook_WalkingRight);
				MySprite->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
				break;
			}
	case KnightAnimationState::AS_DEAD:
		{
		UGameplayStatics::OpenLevel(GetWorld(), "L_GameOver");
		break;
		}
	case KnightAnimationState::AS_WON:
		{
			UGameplayStatics::OpenLevel(GetWorld(), "L_WinScreen");
			break;
		}
	}
}

// Sets default values
AMario::AMario()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MarioBodySprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MarioBodyCapsule"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MarioSpringArm"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MarioBodyCamera"));
	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	MySpringArm->SetupAttachment(RootComponent);
	MyCamera->SetupAttachment(MySpringArm);
}

// Called when the game starts or when spawned
void AMario::BeginPlay()
{
	Super::BeginPlay();
	CurrentAnimationState = KnightAnimationState::AS_IDLE;
	OldAnimationState = KnightAnimationState::AS_EMPTY;
	ProcessAnimStateMachine();
	MyBodyCollider->OnComponentHit.AddDynamic(this, &AMario::OnCollision);
}

// Called every frame
void AMario::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.X = FMath::Clamp(ClampedSpeed.X, -PlayerMaxSpeed, PlayerMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);

	IdentifyAnimStates();
	ProcessAnimStateMachine();
}

// Called to bind functionality to input
void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Horizontal", this, &AMario::MovePlayerHorizontal);
	InputComponent->BindAction("Fire", IE_Pressed, this, &AMario::Jump);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMario::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->Tags.Contains("Floor"))
	{
		bIsJumping = false;
	}

	else if (OtherActor->Tags.Contains("Water"))
	{
		KillMario();
	}
}

void AMario::KillMario()
{
	UE_LOG(LogTemp, Warning, TEXT("Mario is Dead"));
	CurrentAnimationState = KnightAnimationState::AS_DEAD;
	ProcessAnimStateMachine();
}

void AMario::WinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("You Won!"));
	CurrentAnimationState = KnightAnimationState::AS_WON;
	ProcessAnimStateMachine();
}

void AMario::BounceMario(float force)

{
		//// Get the current velocity
		FVector currentVelocity = MyBodyCollider->GetPhysicsLinearVelocity();

		//// Set the Z component (vertical component) of the velocity to 0
		currentVelocity.Z = 0;
		MyBodyCollider->SetPhysicsLinearVelocity(currentVelocity);

		// Now apply the impulse
		MyBodyCollider->AddImpulse(FVector(0, 0, force));
}

