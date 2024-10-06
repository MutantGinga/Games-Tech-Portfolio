// Fill out your copyright notice in the Description page of Project Settings.


#include "Crate.h"
#include "Mario.h"
#include <PaperSpriteComponent.h>
#include <Components/BoxComponent.h>

// Sets default values
ACrate::ACrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Crate Sprite"));
	UnbreakableBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Unbreakable Box"));
	UnbreakableBox->SetBoxExtent(FVector(32, 32, 32));
	BreakableBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Breakable Box"));
	BreakableBox->SetBoxExtent(FVector(32, 32, 32));

	RootComponent = MySprite;
	UnbreakableBox->SetupAttachment(RootComponent);
	BreakableBox->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACrate::BeginPlay()
{
	Super::BeginPlay();
	BreakableBox->OnComponentBeginOverlap.AddDynamic(this, &ACrate::OnOverlap);
}

// Called every frame
void ACrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrate::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Crate Destroyed"));
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		Destroy();
	}

}

