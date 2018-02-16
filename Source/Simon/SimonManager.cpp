// Fill out your copyright notice in the Description page of Project Settings.

#include "SimonManager.h"
#include "SimonBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"


// Sets default values
ASimonManager::ASimonManager()
{
	Super::BeginPlay();
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	colors.Add(TEXT("RED"));
	colors.Add(TEXT("GREEN"));
	colors.Add(TEXT("BLUE"));
	colors.Add(TEXT("YELLOW"));

}

// Called when the game starts or when spawned
void ASimonManager::BeginPlay()
{
	Super::BeginPlay();

	for (auto color : colors)
	{
		ASimonBlock* NewBlock = GetWorld()->SpawnActor<ASimonBlock>();

		if (NewBlock != nullptr)
		{
			NewBlock->SetMaterial(color);
		}
	}
	
}

// Called every frame
void ASimonManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

