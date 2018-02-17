// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "SimonBlock.generated.h"

/** A block that can be clicked */
UCLASS(minimalapi)
class ASimonBlock : public AActor
{
	GENERATED_BODY()

	/** Dummy root component */
	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* DummyRoot;

	/** SkeletalMesh component for the clickable block */
	UPROPERTY()
		TWeakObjectPtr<USkeletalMeshComponent> BlockMesh;

public:
	ASimonBlock();

	/** Are we currently active? */
	bool bIsActive;

	/** String to know in an efficient way which is my color*/
	FString Color;

	/** Pointer to the actual material */
	UPROPERTY()
		class UMaterial* GreenMaterial;
	UPROPERTY()
		class UMaterial* RedMaterial;
	UPROPERTY()
		class UMaterial* BlueMaterial;
	UPROPERTY()
		class UMaterial* YellowMaterial;

	/** Audio variables: SoundCue and AudioComponent*/
	UPROPERTY()
		class USoundBase* ActivatedSoundGreen;
	UPROPERTY()
		class USoundBase* ActivatedSoundRed;
	UPROPERTY()
		class USoundBase* ActivatedSoundBlue;
	UPROPERTY()
		class USoundBase* ActivatedSoundYellow;

	UPROPERTY()
		class UAudioComponent* ActivatedAudioComponent;



	void Activate() const;

	void SetMaterial(FString Color);
};



