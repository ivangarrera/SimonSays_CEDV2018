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
		TArray<TSharedPtr<FJsonValue>> ObjArray = JsonObject->GetArrayField(TEXT("Records"));
		
		for (int32 i = 0; i < ObjArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> Value = ObjArray[i];
			TSharedPtr<FJsonObject> Json = Value->AsObject();
      
			FString Name = Json->GetStringField(TEXT("Name"));
			FString Round = Json->GetStringField(TEXT("Round"));

			// Add the values readed, into corresponding arrays
			RecordNames.Add(Name);
			RecordPunctuations.Add(Round);
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
			"Round":"the_round"
		}
	*/
	
	if (RecordNames.Num() == RecordPunctuations.Num())
	{
		for (int32 Index = 0; Index < RecordNames.Num(); Index++)
		{
			TSharedPtr<FJsonObject> JsonRecordObject = MakeShareable(new FJsonObject());
			JsonRecordObject->SetStringField("Name", RecordNames[Index]);
			JsonRecordObject->SetStringField("Round", RecordPunctuations[Index]);
			TSharedRef<FJsonValueObject> JsonValue = MakeShareable(new FJsonValueObject(JsonRecordObject));

			// Add the Record Object to JSON Array
			RecordsArray.Add(JsonValue);
		}
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

void ASimonGameMode::SetPianoAudio(bool piano)
{
	Piano = piano;
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString("Piano was set to: ") + (Piano ? FString("true") : FString("false")));
}

bool ASimonGameMode::GetPiano() const
{
	return Piano;
}
