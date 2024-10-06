// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PeggleBallLauncher.h"
#include "PaperSpriteComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PeggleBlock.generated.h"

UCLASS()
class PONG_API APeggleBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeggleBlock();
	UPROPERTY(VisibleAnywhere, Category = "Sprites");
	class UPaperSpriteComponent* MySprite;
	APeggleBallLauncher* Launcher;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* MyCollider;
	UPROPERTY(EditAnywhere, Category = "Block Stats");
	bool RotateTrue;
	UPROPERTY(EditAnywhere, Category = "Block Stats");
	bool MoveTrue;
	UPROPERTY(EditAnywhere, Category = "Block Stats");
	bool IsMultiballMaster = 0;
	UPROPERTY(EditAnywhere, Category = "Block Stats");
	bool IsSpookyMaster = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	FTimerHandle DestroyTimer;
	void DestroyThisObject();
	FQuat MyQuat;
	FVector MyVelocity;
	FVector MyStartLocation;

};
