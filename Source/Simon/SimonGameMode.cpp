// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonGameMode.h"
#include "SimonPlayerController.h"
#include "Engine.h"
#include "Json.h"
#include "SimonPawn.h"

ASimonGameMode::ASimonGameMode() : bIsEasy(false), bIsMedium(false), bIsHard(false), bIsEndless(false)
{
	// no pawn by default
	DefaultPawnClass = ASimonPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ASimonPlayerController::StaticClass();
}

void ASimonGameMode::ReadJsonFile()
{
	// Read Json File into TMap
	FString FullPath = FPaths::ProjectDir() + "Content/Data/Records.json";
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = FJsonStringReader::Create(JsonStr);

	TSharedPtr<FJsonObject> JsonObject =  MakeShareable(new FJsonObject());
	
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("Records"));
		
		for (int32 i = 0; i < objArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> value = objArray[i];
			TSharedPtr<FJsonObject> json = value->AsObject();

			FString name = json->GetStringField(TEXT("Name"));
			FString round = json->GetStringField(TEXT("Round"));
			RecordsMap.Emplace(name, round);
		}
	}
}

void ASimonGameMode::WriteJsonFile()
{
	// Main JSON object
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	
	// JSON Array to store Records object
	TArray<TSharedPtr<FJsonValue>> RecordsArray;

	// Record object. It has the following form:
	/*  {
			"Name":"the_name",
			"Round":"th_round"
		}
	*/
	TSharedPtr<FJsonObject> JsonRecordObject = MakeShareable(new FJsonObject());
	
	for (auto& Elem : RecordsMap)
	{
		JsonRecordObject->SetStringField("Name", Elem.Key);
		JsonRecordObject->SetStringField("Round", *Elem.Value);
		TSharedRef<FJsonValueObject> JsonValue = MakeShareable(new FJsonValueObject(JsonRecordObject));

		// Add the Record Object to JSON Array
		RecordsArray.Add(JsonValue);
	}
	// Add the JSON Array to main JSON Object
	JsonObject->SetArrayField("Records", RecordsArray);

	// Write JSON Object to JSON file
	FString FullPath = FPaths::ProjectDir() + "Content/Data/Records.json";
	FString JsonStr;
	TSharedRef< TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonStr);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	FFileHelper::SaveStringToFile(*JsonStr, *FullPath);
}

void ASimonGameMode::SetVolume(float volume)
{
	Volume = volume;
}

float ASimonGameMode::GetVolume() const
{
	return Volume;
}
