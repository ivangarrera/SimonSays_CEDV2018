// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonManager.h"
#include "SimonPawn.h"
#include "SimonGameMode.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"


// Sets default values
ASimonManager::ASimonManager() : AccumulatedDeltaTime(0.0f), ShowAnother(1.f), PickAnotherBlock(2.f), Counter(0), isPlaying(false), IndexCurrentBlock(0),
								 NumberOfBlocksToGoFaster(4), AmmountOfTimeToDecrease(0.25f), NumberOfRounds(0), RoundsCounter(0)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	colors.Add(TEXT("RED"));
	colors.Add(TEXT("GREEN"));
	colors.Add(TEXT("BLUE"));
	colors.Add(TEXT("YELLOW"));

}

// Called when the game starts or when spawned
void ASimonManager::BeginPlay()
{
	Super::BeginPlay();

	// Create the widget that is going to be displayed when the game is going to start
	if (WGameStart)
	{
		pWGameStart = CreateWidget<UUserWidget>(GetGameInstance(), WGameStart);
		if (pWGameStart)
		{
			pWGameStart->AddToViewport();
			UGameplayStatics::SetGamePaused(this, true);
		}
	}

	FVector Location(0.0f, 0.0f, 20.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FVector Scale(175.f, 175.f, 1.f);

	for (auto color : colors)
	{

		FTransform transform(Rotation, Location, Scale);
		ASimonBlock* NewBlock = GetWorld()->SpawnActor<ASimonBlock>(ASimonBlock::StaticClass(), transform);

		if (NewBlock != nullptr)
		{
			NewBlock->SetMaterial(color);
		}

		Blocks.Add(NewBlock);

		Rotation.Yaw -= 90;
	}

	//Get a reference to the player pawn
	PlayerPawn = Cast<ASimonPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	// Create the widget that is going to be displayed when the game ends.
	if (WGameEnd)
	{
		pWGameEnd = CreateWidget<UUserWidget>(GetGameInstance(), WGameEnd);
	}

	// Create the widget that is going to be displayed when the player win
	if (WWinGame)
	{
		pWWinGame = CreateWidget<UUserWidget>(GetGameInstance(), WWinGame);
	}
}

// Called every frame
void ASimonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;

	//If the there are still blocks in the sequence
	if (AccumulatedDeltaTime > ShowAnother && Counter < Sequence.Num() && !isPlaying)
	{
		Sequence[Counter]->Activate();
		Counter++;

		AccumulatedDeltaTime = 0.f;

		if (Counter == Sequence.Num())
		{
			isPlaying = true;
			RoundsCounter += 1;
		}
	}

	// If it's been a long time since you pressed a block, restart the level
	if (AccumulatedDeltaTime >= PickAnotherBlock)
	{
		if (pWGameEnd)
		{
			pWGameEnd->AddToViewport();
			UGameplayStatics::SetGamePaused(this, true);
		}
	}

	//If the sequence has finished, add another block
	if (Counter == Sequence.Num() && !isPlaying 
		&& RoundsCounter <= NumberOfRounds)
	{
		Sequence.Add(GetRandomBlock());
		Counter = 0;
	}

	// YOU WIN
	if (RoundsCounter >= NumberOfRounds)
	{
		if (pWWinGame)
		{
			pWGameStart->AddToViewport();
			UGameplayStatics::SetGamePaused(this, true);
		}
	}
}

ASimonBlock* ASimonManager::GetRandomBlock() const
{
	return Blocks[FMath::RandRange(0, Blocks.Num() - 1)];
}

void ASimonManager::NotifyBlockClicked(ASimonBlock* Block)
{
	// If you Hit enough blocks, the difficulty will increase
	if (((IndexCurrentBlock + 1) % NumberOfBlocksToGoFaster) == 0)
	{
		IncreaseSpeed();
	}

	// Check whether the block clicked is ok or not
	if (Sequence[IndexCurrentBlock]->GetName().Equals(Block->GetName()))
	{
		IndexCurrentBlock += 1;
		AccumulatedDeltaTime = 0.f;
	}
	else
	{
		// If you fail the sequence, restart the level
		if (pWGameEnd)
		{
			pWGameEnd->AddToViewport();
			UGameplayStatics::SetGamePaused(this, true);
		}
	}

	if (IndexCurrentBlock == Sequence.Num())
	{
		IndexCurrentBlock = 0;
		isPlaying = false;
		AccumulatedDeltaTime = 0.f;
	}
	
}

void ASimonManager::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ASimonManager::GameModeIsReady()
{
	// It is supposed that only one is true at the same time
	if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->bIsEasy)
	{
		NumberOfRounds = 6;
	}
	else if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->bIsMedium)
	{
		NumberOfRounds = 10;
	}
	else if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->bIsHard)
	{
		NumberOfRounds = 16;
	}
	else if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->bIsEndless)
	{
		NumberOfRounds = MAX_int32;
	}
}

void ASimonManager::IncreaseSpeed()
{
	ShowAnother -= AmmountOfTimeToDecrease;
	PickAnotherBlock -= AmmountOfTimeToDecrease;
	NumberOfBlocksToGoFaster += 4;

	for (auto block : Blocks)
	{
		block->IncreasePitch();
	}
}
