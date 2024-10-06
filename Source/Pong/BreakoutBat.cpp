// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBat.h"

void ABreakoutBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(speed * input, 0, 0));
}

void ABreakoutBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InputComponent->BindAxis("Horizontal", this, &ABreakoutBat::MovePlayer);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

