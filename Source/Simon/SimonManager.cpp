// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonManager.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"


// Sets default values
ASimonManager::ASimonManager() : AccumulatedDeltaTime(0.0f), ShowAnother(1.f), Counter(0)
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

		Rotation.Yaw += 90;
	}
	
}

// Called every frame
void ASimonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AccumulatedDeltaTime += DeltaTime;

	//If the there are still blocks in the sequence
	if (AccumulatedDeltaTime > ShowAnother && Counter < Sequence.Num())
	{
		Sequence[Counter]->Activate();
		Counter++;

		AccumulatedDeltaTime = 0.f;
	}
	//If the sequence has finished, add another block
	if (Counter == Sequence.Num())
	{
		Sequence.Add(GetRandomBlock());
		Counter = 0;
	}

}

ASimonBlock* ASimonManager::GetRandomBlock() const
{
	return Blocks[FMath::RandRange(0, Blocks.Num() - 1)];
}
