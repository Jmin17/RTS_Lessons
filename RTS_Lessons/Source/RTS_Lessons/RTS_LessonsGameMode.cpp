// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RTS_LessonsGameMode.h"
#include "RTS_LessonsPlayerController.h"
#include "RTS_LessonsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "CameraPawnBase.h"

ARTS_LessonsGameMode::ARTS_LessonsGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTS_LessonsPlayerController::StaticClass();

	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Classes_Game/RTS_Lessons/CameraPawnBase"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//	
	//}
	DefaultPawnClass = ACameraPawnBase::StaticClass();

}