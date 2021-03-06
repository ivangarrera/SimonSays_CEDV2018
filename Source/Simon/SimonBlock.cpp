// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonBlock.h"
#include "Components/AudioComponent.h"
#include "SimonGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstance.h"

ASimonBlock::ASimonBlock() : bIsActive(false), pitch(1.0f)
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

	auto GSoundP = ConstructorHelpers::FObjectFinder<USoundCue>(TEXT("'/Game/Audio/GreenSoundCuePiano.GreenSoundCuePiano'"));
	auto RSoundP = ConstructorHelpers::FObjectFinder<USoundCue>(TEXT("'/Game/Audio/RedSoundCuePiano.RedSoundCuePiano'"));
	auto BSoundP = ConstructorHelpers::FObjectFinder<USoundCue>(TEXT("'/Game/Audio/BlueSoundCuePiano.BlueSoundCuePiano'"));
	auto YSoundP = ConstructorHelpers::FObjectFinder<USoundCue>(TEXT("'/Game/Audio/YellowSoundCuePiano.YellowSoundCuePiano'"));

	auto GMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialGreen.SimonBlock_MaterialGreen'"));
	auto RMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialRed.SimonBlock_MaterialRed'"));
	auto BMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialBlue.SimonBlock_MaterialBlue'"));
	auto YMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialYellow.SimonBlock_MaterialYellow'"));

	auto GCBMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialGreen_CB.SimonBlock_MaterialGreen_CB'"));
	auto YCBMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialYellow_CB.SimonBlock_MaterialYellow_CB'"));

	auto GHMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialGreen_Highlighted.SimonBlock_MaterialGreen_Highlighted'"));
	auto RHMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialRed_Highlighted.SimonBlock_MaterialRed_Highlighted'"));
	auto BHMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialBlue_Highlighted.SimonBlock_MaterialBlue_Highlighted'"));
	auto YHMaterial = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Models/Mesh/SimonBlock/SimonBlock_MaterialYellow_Highlighted.SimonBlock_MaterialYellow_Highlighted'"));

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

	ActivatedSoundGreenPiano = GSoundP.Object;
	ActivatedSoundRedPiano = RSoundP.Object;
	ActivatedSoundBluePiano = BSoundP.Object;
	ActivatedSoundYellowPiano = YSoundP.Object;

	GreenHighlightMaterial = GHMaterial.Object;
	RedHighlightMaterial = RHMaterial.Object;
	BlueHighlightMaterial = BHMaterial.Object;
	YellowHighlightMaterial = YHMaterial.Object;

	GreenMaterial = GMaterial.Object;
	RedMaterial = RMaterial.Object;
	BlueMaterial = BMaterial.Object;
	YellowMaterial = YMaterial.Object;

	GreenCBMaterial = GCBMaterial.Object;
	YellowCBMaterial = YCBMaterial.Object;

	ActivatedAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ActivatedAudioComponent"));

}


void ASimonBlock::SetMaterial(FString Color, bool IsColorblind)
{
	if (Color.Equals("GREEN"))
	{
		// The material to set is Green
		BlockMesh->SetStaticMesh(GreenMesh);
		if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->GetPiano())
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundGreenPiano);
		}
		else
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundGreen);
		}
	}
	else if (Color.Equals("RED"))
	{
		// The material to set is Red
		BlockMesh->SetStaticMesh(RedMesh);
		if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->GetPiano())
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundRedPiano);
		}
		else
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundRed);
		}
	}
	else if (Color.Equals("BLUE"))
	{
		// The material to set is Blue
		BlockMesh->SetStaticMesh(BlueMesh);
		if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->GetPiano())
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundBluePiano);
		}
		else
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundBlue);
		}
	}
	else if (Color.Equals("YELLOW"))
	{
		// The material to set is Yellow
		BlockMesh->SetStaticMesh(YellowMesh);
		if (GetWorld()->GetAuthGameMode<ASimonGameMode>()->GetPiano())
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundYellowPiano);
		}
		else
		{
			ActivatedAudioComponent->SetSound(ActivatedSoundYellow);
		}
	}

	if (IsColorblind)
	{
		GreenMaterial = GreenCBMaterial;
		YellowMaterial = YellowMaterial;
		if (Color.Equals("GREEN"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(GreenMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("YELLOW"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(YellowMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
	}

	ActivatedAudioComponent->SetVolumeMultiplier(GetWorld()->GetAuthGameMode<ASimonGameMode>()->GetVolume());
	this->Color = Color;
}

void ASimonBlock::Activate() const
{
	ActivatedAudioComponent->Play();
	Highlight(true);
}

void ASimonBlock::Activate(bool bHighlight) const
{
	ActivatedAudioComponent->Play();
	if (bHighlight)
		Highlight(true);
}

void ASimonBlock::Deactivate() const
{
	Highlight(false);
}

void ASimonBlock::Highlight(bool bHighlight) const
{
	if (bHighlight)
	{
		if (Color.Equals("GREEN"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(GreenHighlightMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("RED"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(RedHighlightMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("BLUE"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(BlueHighlightMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("YELLOW"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(YellowHighlightMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
	}
	else
	{
		if (Color.Equals("GREEN"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(GreenMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("RED"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(RedMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("BLUE"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(BlueMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
		else if (Color.Equals("YELLOW"))
		{
			auto GDynamicMaterial = UMaterialInstanceDynamic::Create(YellowMaterial, BlockMesh.Get());
			BlockMesh->SetMaterial(0, GDynamicMaterial);
		}
	}
}

void ASimonBlock::OnMouseHover(bool bHovered) const
{
	BlockMesh->SetRenderCustomDepth(bHovered);
}

void ASimonBlock::IncreasePitch()
{
	pitch += 0.1f;
	ActivatedAudioComponent->SetPitchMultiplier(pitch);
}