// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "SimonPlayerController.h"

ASimonPlayerController::ASimonPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
