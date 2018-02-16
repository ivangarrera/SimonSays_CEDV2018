// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonBlock.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ASimonBlock::ASimonBlock() : bIsActive(false)
{

	// Structure to hold one-time initialization

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> YellowMaterial;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> GreenSound;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> RedSound;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> BlueSound;
		ConstructorHelpers::FObjectFinderOptional<USoundCue> YellowSound;

		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock.SimonBlock"))
			, GreenMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialGreen.SimonBlock_MaterialGreen"))
			, RedMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialRed.SimonBlock_MaterialRed"))
			, BlueMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialBlue.SimonBlock_MaterialBlue"))
			, YellowMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialYellow.SimonBlock_MaterialYellow"))
			, GreenSound(TEXT("/Game/Audio/GreenSound.GreenSoundCue"))
			, RedSound(TEXT("/Game/Audio/GreenSound.GreenSoundCue"))
			, BlueSound(TEXT("/Game/Audio/GreenSound.GreenSoundCue"))
			, YellowSound(TEXT("/Game/Audio/GreenSound.GreenSoundCue"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component	
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	BlockMesh->SetupAttachment(DummyRoot);

	GreenMaterial = ConstructorStatics.GreenMaterial.Get();
	RedMaterial = ConstructorStatics.RedMaterial.Get();
	BlueMaterial = ConstructorStatics.BlueMaterial.Get();
	YellowMaterial = ConstructorStatics.YellowMaterial.Get();

	ActivatedSoundGreen = ConstructorStatics.GreenSound.Get();
	ActivatedSoundRed = ConstructorStatics.RedSound.Get();
	ActivatedSoundBlue = ConstructorStatics.BlueSound.Get();
	ActivatedSoundYellow = ConstructorStatics.YellowSound.Get();

	ActivatedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ActivatedAudioComponent"));
	
}

void ASimonBlock::SetMaterial(FString Color)
{

	if (Color.Equals("Green"))
	{
		// The material to set is Green
		BlockMesh->SetMaterial(0, GreenMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundGreen);
	}
	else if (Color.Equals("Red"))
	{
		// The material to set is Red
		BlockMesh->SetMaterial(0, RedMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundRed);
	}
	else if (Color.Equals("Blue"))
	{
		// The material to set is Blue
		BlockMesh->SetMaterial(0, BlueMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundBlue);
	}
	else if (Color.Equals("Yellow"))
	{
		// The material to set is Yellow
		BlockMesh->SetMaterial(0, YellowMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundYellow);
	}
}

void ASimonBlock::Activate() const
{
	ActivatedAudioComponent->Play();
}

