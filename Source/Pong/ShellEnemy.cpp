// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellEnemy.h"
#include "Mario.h"

void AShellEnemy::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnHeadOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Shell Spawned"));
		FVector Location = GetActorLocation();
		FVector BoxExtent = HeadTrigger->GetScaledBoxExtent();
		Location.Z += 2 * BoxExtent.Z;
		SpawnTransform.SetLocation(Location);
		AActor* Powerup = GetWorld()->SpawnActor<AActor>(ShellBPClass, SpawnTransform);
	}
}
