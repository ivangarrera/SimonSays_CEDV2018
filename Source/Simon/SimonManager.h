// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimonBlock.h"
#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "SimonManager.generated.h"

UCLASS()
class SIMON_API ASimonManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimonManager();

	TArray<FString> colors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void NotifyBlockClicked(ASimonBlock* Block);

	UPROPERTY(EditAnywhere, Category = "Widgets")
		TSubclassOf<class UUserWidget> WGameEnd;

	TWeakObjectPtr<class UUserWidget> pWGameEnd;
	
private:
	// Array to keep the reference of the 4 blocks
	TArray<ASimonBlock*> Blocks;

	// Arrays to control the sequence: Total Sequence and Sequence in construction.
	TArray<ASimonBlock*> Sequence;

	// Counter to know the state of the sequence when showing it
	int Counter;

	float AccumulatedDeltaTime;

	//Timer to show the sequence every number of seconds (Should change with difficulty or time)
	float ShowAnother;

	// Ammount of time the user has to pick another block
	float PickAnotherBlock;

	bool isPlaying;

	// Counter to know if the player is hitting blocks in correct order
	int IndexCurrentBlock;

	// Every time you hit NumberOfBlocksToGoFaster Blocks, the sequence will go faster, 
	// and you must enter the sequence faster, too.
	int NumberOfBlocksToGoFaster;

	// Amount of time in which ShowAnother and PickAnotherBlock will decrease
	float AmmountOfTimeToDecrease;

	UPROPERTY()
		class ASimonPawn* PlayerPawn;

	ASimonBlock* GetRandomBlock() const;
	
	void RestartLevel();
};
