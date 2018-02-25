// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonManager.h"
#include "math.h"
#include "SimonPawn.h"
#include "SimonGameMode.h"
#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"


// Sets default values
ASimonManager::ASimonManager() : AccumulatedDeltaTime(0.0f), ShowAnother(1.f), PickAnotherBlock(5.f), Counter(0), isPlaying(false), IndexCurrentBlock(0),
								 NumberOfBlocksToGoFaster(4), NumberOfRounds(0), RoundsCounter(0), Won(false)
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

	// Create the widget to see the score obtained
	if (WScore)
	{
		pWScore = CreateWidget<UUserWidget>(GetGameInstance(), WScore);
	}

	// Retrieve the RecordManager actor
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->GetName().Contains(FString("RecordManager")))
		{
			// Conversion to smart pointer
			pRecordManager = Cast<ARecordManager>(*ActorItr);
			break;
		}
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
		if (Counter > 0)
			Sequence[Counter - 1]->Deactivate();
		Sequence[Counter]->Activate();
		Counter++;

		AccumulatedDeltaTime = 0.f;

		if (Counter == Sequence.Num())
		{
			isPlaying = true;
			RoundsCounter += 1;
		}
	}
	if (AccumulatedDeltaTime > ShowAnother && Counter == Sequence.Num())
	{
		Sequence[Counter - 1]->Deactivate();
	}

	// If it's been a long time since you pressed a block, restart the level
	if (AccumulatedDeltaTime >= PickAnotherBlock)
	{
		if (pWGameEnd)
		{
			pWGameEnd->AddToViewport();
			UGameplayStatics::SetGamePaused(this, true);

			// Add new punctuation if modality is Endless
			if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->bIsEndless)
			{
				// Show the score widget
				pWScore->AddToViewport();
			}
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
	if (RoundsCounter >= NumberOfRounds && Won)
	{
		if (pWWinGame)
		{
			pWWinGame->AddToViewport();
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
		IncreaseSpeed(IndexCurrentBlock + 1);
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

			// Add new punctuation if modality is Endless
			if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->bIsEndless)
			{
				// Show the widget
				pWScore->AddToViewport();
			}
		}
	}

	// If you get the whole sequence right
	if (IndexCurrentBlock == Sequence.Num())
	{
		if (IndexCurrentBlock == NumberOfRounds)
		{
			Won = true;
		}

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

void ASimonManager::IncreaseSpeed(double Round)
{
	// Calculate the logarithm in base 60 (so the speed increases accordingly)(This means top wave is 60
	double NewTime = 1 - (log(Round) / log(60));

	ShowAnother = NewTime;
	PickAnotherBlock -= NewTime;
	NumberOfBlocksToGoFaster += 4;

	for (auto block : Blocks)
	{
		block->IncreasePitch();
	}
}

void ASimonManager::AddCurrentRecord(FString Name)
{
	pRecordManager->ReadJsonFile();
	FString Punctuation = "";
	Punctuation.AppendInt(RoundsCounter);
	pRecordManager->RecordsScores.Add(TTuple<FString, FString>(Name, Punctuation));
}
