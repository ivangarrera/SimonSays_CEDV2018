// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SimonPawn.generated.h"

UCLASS(config=Game)
class ASimonPawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

protected:
	virtual void BeginPlay() override;

	void TriggerClick();
	void TraceForBlock(const FVector& Start, const FVector& End);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		class ASimonBlock* CurrentBlockFocus;

private:

	TWeakObjectPtr<class ASimonManager> SimonManager;
};
