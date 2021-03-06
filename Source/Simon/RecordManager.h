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

	// Widget to show the records
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> WRecords;
	
	UPROPERTY()
	class UUserWidget* pWRecords;

	UPROPERTY()
	class UTextBlock* pWRecordsText;

	static TArray<TTuple<FString, FString>> RecordsScores;

	void ReadJsonFile();

	UFUNCTION(BlueprintCallable)
		void WriteJsonFile();

	inline static bool ConstPredicate(const TTuple<FString, FString>& ip1, const TTuple<FString, FString>& ip2)
	{
		int32 val1 = FCString::Atoi(*ip1.Value);
		int32 val2 = FCString::Atoi(*ip2.Value);
		return (val1 > val2);
	}
};
