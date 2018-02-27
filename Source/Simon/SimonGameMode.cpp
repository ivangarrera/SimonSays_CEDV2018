// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonGameMode.h"
#include "SimonPlayerController.h"
#include "Engine.h"
#include "Json.h"
#include "SimonPawn.h"

ASimonGameMode::ASimonGameMode() : bIsEasy(false), bIsMedium(false), bIsHard(false), bIsEndless(false)
{
	// no pawn by default
	DefaultPawnClass = ASimonPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ASimonPlayerController::StaticClass();
}

void ASimonGameMode::SetVolume(float volume)
{
	Volume = volume;
}

float ASimonGameMode::GetVolume() const
{
	return Volume;
}

void ASimonGameMode::SetPianoAudio(bool piano)
{
	Piano = piano;
}

bool ASimonGameMode::GetPiano() const
{
	return Piano;
}

void ASimonGameMode::SetColorBlind(bool IsColorblind)
{
	ColorBlind = IsColorblind;
}

bool ASimonGameMode::GetColorBlind() const
{
	return ColorBlind;
}
