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

	auto GMesh = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("StaticMesh'/Game/Models/Mesh/SimonBlock/SimonBlockGreen.SimonBlockGreen'"));
	auto RMesh = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("StaticMesh'/Game/Models/Mesh/SimonBlock/SimonBlockRed.SimonBlockRed'"));
	auto BMesh = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("StaticMesh'/Game/Models/Mesh/SimonBlock/SimonBlockBlue.SimonBlockBlue'"));
	auto YMesh = ConstructorHelpers::FObjectFinder<UStaticMesh> (TEXT("StaticMesh'/Game/Models/Mesh/SimonBlock/SimonBlockYellow.SimonBlockYellow'"));

	auto GSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/GreenSoundCue.GreenSoundCue'"));
	auto RSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/RedSoundCue.RedSoundCue'"));
	auto BSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/BlueSoundCue.BlueSoundCue'"));
	auto YSound = ConstructorHelpers::FObjectFinder<USoundCue> (TEXT("'/Game/Audio/YellowSoundCue.YellowSoundCue'"));

	// Create dummy root scene component	
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));
	BlockMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	BlockMesh->SetupAttachment(DummyRoot);
	
	BlockMesh->SetNotifyRigidBodyCollision(true);

	GreenMesh = GMesh.Object;
	RedMesh = RMesh.Object;
	BlueMesh = BMesh.Object;
	YellowMesh = YMesh.Object;

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
		BlockMesh->SetStaticMesh(GreenMesh);
		ActivatedAudioComponent->SetSound(ActivatedSoundGreen);
	}
	else if (Color.Equals("RED"))
	{
		// The material to set is Red
		BlockMesh->SetStaticMesh(RedMesh);
		ActivatedAudioComponent->SetSound(ActivatedSoundRed);
	}
	else if (Color.Equals("BLUE"))
	{
		// The material to set is Blue
		BlockMesh->SetStaticMesh(BlueMesh);
		ActivatedAudioComponent->SetSound(ActivatedSoundBlue);
	}
	else if (Color.Equals("YELLOW"))
	{
		// The material to set is Yellow
		BlockMesh->SetStaticMesh(YellowMesh);
		ActivatedAudioComponent->SetSound(ActivatedSoundYellow);
	}
}

void ASimonBlock::Activate() const
{
	ActivatedAudioComponent->Play();
	BlockMesh->SetRenderCustomDepth(true);
}

