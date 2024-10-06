// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioGameModeBase.h"

void AMarioGameModeBase::ResetScore()
{
	PlayerScore = 0;
}

void AMarioGameModeBase::AddScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}

int AMarioGameModeBase::GetScore()
{
	return PlayerScore;
}
