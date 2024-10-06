// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerCrate.h"
#include <Components/BoxComponent.h>
#include "Mario.h"

void APowerCrate::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Crate Destroyed"));
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		FVector Location = GetActorLocation();
		FVector BoxExtent = UnbreakableBox->GetScaledBoxExtent();
		Location.Z += 2 * BoxExtent.Z;
		SpawnTransform.SetLocation(Location);
		AActor* Powerup = GetWorld()->SpawnActor<AActor>(CoinBPClass, SpawnTransform);
	}
}
