// Fill out your copyright notice in the Description page of Project Settings.

#include "RecordManager.h"
#include "SimonGameMode.h"
#include "Blueprint/UserWidget.h"
#include "TextWidgetTypes.h"
#include "TextBlock.h"
#include "Engine.h"


// Sets default values
ARecordManager::ARecordManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RecordsText = FString("");
}

// Called when the game starts or when spawned
void ARecordManager::BeginPlay()
{
	Super::BeginPlay();

	// Load JSON data
	GetWorld()->GetAuthGameMode<ASimonGameMode>()->ReadJsonFile();

	if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->RecordNames.Num() == GetWorld()->GetAuthGameMode<ASimonGameMode>()->RecordPunctuations.Num())
	{
		for (int32 Index = 0; Index < GetWorld()->GetAuthGameMode<ASimonGameMode>()->RecordNames.Num(); Index++)
		{
			FString Name = GetWorld()->GetAuthGameMode<ASimonGameMode>()->RecordNames[Index];
			FString Punctuation = GetWorld()->GetAuthGameMode<ASimonGameMode>()->RecordPunctuations[Index];
			RecordsText += (Name + " : " + Punctuation + "\n");
		}
	}
	
	// Create the Records Widget
	if (WRecords)
	{
		pWRecords = CreateWidget<UUserWidget>(GetGameInstance(), WRecords);
		if (pWRecords)
		{
			pWRecords->AddToViewport();
			pWRecordsText = (UTextBlock*)pWRecords->GetWidgetFromName("RecordText");
			pWRecordsText->SetText(FText::FromString(RecordsText));
		}
	}
}

// Called every frame
void ARecordManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

