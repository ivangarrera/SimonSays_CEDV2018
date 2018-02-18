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
		ConstructorHelpers::FObjectFinderOptional<UMaterial> GreenMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> RedMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> BlueMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterial> YellowMaterial;

		FConstructorStatics()
			: GreenMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialGreen.SimonBlock_MaterialGreen"))
			, RedMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialRed.SimonBlock_MaterialRed"))
			, BlueMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialBlue.SimonBlock_MaterialBlue"))
			, YellowMaterial(TEXT("/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialYellow.SimonBlock_MaterialYellow"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	auto StaticMesh = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("StaticMesh'/Game/Models/Mesh/SimonBlock/SimonBlock.SimonBlock'"));

	auto GMaterial = ConstructorHelpers::FObjectFinder<UMaterial> (TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialGreen.SimonBlock_MaterialGreen'"));
	auto RMaterial = ConstructorHelpers::FObjectFinder<UMaterial> (TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialRed.SimonBlock_MaterialRed'"));
	auto BMaterial = ConstructorHelpers::FObjectFinder<UMaterial> (TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialBlue.SimonBlock_MaterialBlue'"));
	auto YMaterial = ConstructorHelpers::FObjectFinder<UMaterial> (TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialYellow.SimonBlock_MaterialYellow'"));

	auto GSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/GreenSoundCue.GreenSoundCue'"));
	auto RSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/RedSoundCue.RedSoundCue'"));
	auto BSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/BlueSoundCue.BlueSoundCue'"));
	auto YSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/YellowSoundCue.YellowSoundCue'"));

	// Create dummy root scene component	
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetStaticMesh(StaticMesh.Object);
	BlockMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	BlockMesh->SetupAttachment(DummyRoot);
	
	BlockMesh->SetNotifyRigidBodyCollision(true);

	GreenMaterial = GMaterial.Object;
	RedMaterial = RMaterial.Object;
	BlueMaterial = BMaterial.Object;
	YellowMaterial = YMaterial.Object;

	ActivatedSoundGreen = GSound.Object;
	ActivatedSoundRed = RSound.Object;
	ActivatedSoundBlue = BSound.Object;
	ActivatedSoundYellow = YSound.Object;

	ActivatedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ActivatedAudioComponent"));

}


void ASimonBlock::SetMaterial(FString Color)
{

	if (Color.Equals("GREEN"))
	{
		// The material to set is Green
		BlockMesh->SetMaterial(0, GreenMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundGreen);
	}
	else if (Color.Equals("RED"))
	{
		// The material to set is Red
		BlockMesh->SetMaterial(0, RedMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundRed);
	}
	else if (Color.Equals("BLUE"))
	{
		// The material to set is Blue
		BlockMesh->SetMaterial(0, BlueMaterial);
		ActivatedAudioComponent->SetSound(ActivatedSoundBlue);
	}
	else if (Color.Equals("YELLOW"))
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

