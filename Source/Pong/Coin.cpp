// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "MarioGameModeBase.h"
#include "Mario.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	MySprite->OnComponentBeginOverlap.AddDynamic(this, &ACoin::BeginOverlap);
	RootComponent = MySprite;
	/*MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Bat Hit Box"));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetBoxExtent(MySprite->Bounds.GetBox().GetSize());
	MyCollider->SetupAttachment(RootComponent);*/
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoin::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		AMarioGameModeBase* GameMode = Cast<AMarioGameModeBase>(GetWorld()->GetAuthGameMode());
		GameMode->AddScore(1);
		Destroy();
	}
	
}

