// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimonGameMode.generated.h"

/** GameMode class to specify pawn and playercontroller */
UCLASS(minimalapi)
class ASimonGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASimonGameMode();

	// Variables to choose the game mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsEasy;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsMedium;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsHard;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode")
	bool bIsEndless;

	TMultiMap<FString, FString> RecordsMap;

	void ReadJsonFile();
  
	void WriteJsonFile();

	UFUNCTION(BlueprintCallable)
		void SetVolume(float volume);

	UFUNCTION(BlueprintCallable)
		void SetPianoAudio(bool piano);

	float GetVolume() const;
	bool GetPiano() const;
};

static float Volume = 0.75;

static bool Piano = false;