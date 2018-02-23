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

void ASimonGameMode::ReadJsonFile()
{
	// Read Json File into TMap
	FString FullPath = FPaths::ProjectDir() + "Content/Data/Records.json";
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = FJsonStringReader::Create(JsonStr);

	JsonObject =  MakeShareable(new FJsonObject());
	FJsonSerializer::Deserialize(JsonReader, JsonObject);

}

void ASimonGameMode::SetVolume(float volume)
{
	Volume = volume;
}

float ASimonGameMode::GetVolume() const
{
	return Volume;
}
