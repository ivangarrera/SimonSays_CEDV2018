// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RecordManager.generated.h"

UCLASS()
class SIMON_API ARecordManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARecordManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FString RecordsText;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Widget to show the records
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> WRecords;
	
	UPROPERTY()
	class UUserWidget* pWRecords;

	UPROPERTY()
	class UTextBlock* pWRecordsText;
};
