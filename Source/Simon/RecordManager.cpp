// Fill out your copyright notice in the Description page of Project Settings.

#include "RecordManager.h"
#include "SimonGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Engine.h"


// Sets default values
ARecordManager::ARecordManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARecordManager::BeginPlay()
{
	Super::BeginPlay();

	// Load JSON data
	GetWorld()->GetAuthGameMode<ASimonGameMode>()->ReadJsonFile();
	int i = 0;

	for (auto& Elem : GetWorld()->GetAuthGameMode<ASimonGameMode>()->RecordsMap)
	{
		FString Name = Elem.Key;
		FString Rec = *Elem.Value;
		GEngine->AddOnScreenDebugMessage(i, 2.f, FColor::Yellow, Name);
		GEngine->AddOnScreenDebugMessage(i+1, 2.f, FColor::Yellow, Rec);
		i += 2;
	}

	// Create the Records Widget
	if (WRecords)
	{
		pWRecords = CreateWidget<UUserWidget>(GetGameInstance(), WRecords);
		if (pWRecords)
		{
			pWRecords->AddToViewport();
		}
	}
}

// Called every frame
void ARecordManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

