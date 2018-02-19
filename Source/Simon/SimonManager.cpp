// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonManager.h"
#include "SimonPawn.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"


// Sets default values
ASimonManager::ASimonManager() : AccumulatedDeltaTime(0.0f), ShowAnother(1.f), PickAnotherBlock(2.f), Counter(0), isPlaying(false), IndexCurrentBlock(0),
								 NumberOfBlocksToGoFaster(4), AmmountOfTimeToDecrease(0.25f)
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
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Purple, Sequence[Counter]->GetName());
		Counter++;

		AccumulatedDeltaTime = 0.f;

		if (Counter == Sequence.Num())
		{
			isPlaying = true;
		}
	}

	// If it's been a long time since you pressed a block, restart the level
	if (AccumulatedDeltaTime >= PickAnotherBlock)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::White, FString("Too much time. You failed."));
		RestartLevel();
	}

	//If the sequence has finished, add another block
	if (Counter == Sequence.Num() && !isPlaying)
	{
		Sequence.Add(GetRandomBlock());
		Counter = 0;
	}
	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::White, FString::Printf(TEXT("%f, %f"), ShowAnother, PickAnotherBlock));

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
		ShowAnother -= AmmountOfTimeToDecrease;
		PickAnotherBlock -= AmmountOfTimeToDecrease;
		NumberOfBlocksToGoFaster += 4;
	}

	if (Sequence[IndexCurrentBlock]->GetName().Equals(Block->GetName()))
	{
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::White, Block->GetName());
		IndexCurrentBlock += 1;
		AccumulatedDeltaTime = 0.f;
	}
	else
	{
		// If you fail the sequence, restart the level
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::White, FString("You failed, looser."));
		RestartLevel();
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