// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "RTS_LessonsPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "RTS_LessonsCharacter.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/Templates/Casts.h"
#include "Unit.h"
#include "Runtime/Core/Public/Containers/Array.h"


ARTS_LessonsPlayerController::ARTS_LessonsPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ARTS_LessonsPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	//if (bMoveToMouseCursor)
	//{
	//	MoveToMouseCursor();
	//}
}

void ARTS_LessonsPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &ARTS_LessonsPlayerController::SelectUnit);
	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARTS_LessonsPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &ARTS_LessonsPlayerController::OnSetDestinationReleased);

	//// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ARTS_LessonsPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ARTS_LessonsPlayerController::MoveToTouchLocation);

}

void ARTS_LessonsPlayerController::SelectUnit()
{
	FHitResult myHitResult;
	if (GetHitResultUnderCursorByChannel((ETraceTypeQuery)ECollisionChannel::ECC_Visibility, false, myHitResult))
	{
		if (myHitResult.bBlockingHit)
		{
			IUnit* myUnit = Cast<IUnit>(myHitResult.GetActor());
			if (myUnit)
			{
				AActor* myActor = myHitResult.GetActor();
				myUnit->Execute_Select(myActor);

				if (myUnit->Execute_IsSelected(myActor))
				{
					selectedUnits.AddUnique(myUnit);
				}
				else
				{
					selectedUnits.Remove(myUnit);
				}
			}
		}
	}
}

//void ARTS_LessonsPlayerController::OnResetVR()
//{
//	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
//}

//void ARTS_LessonsPlayerController::MoveToMouseCursor()
//{
//	//if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
//	//{
//	//	if (ARTS_LessonsCharacter* MyPawn = Cast<ARTS_LessonsCharacter>(GetPawn()))
//	//	{
//	//		if (MyPawn->GetCursorToWorld())
//	//		{
//	//			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
//	//		}
//	//	}
//	//}
//	//else
//	//{
//	//	// Trace to see what is under the mouse cursor
//	//	FHitResult Hit;
//	//	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
//
//	//	if (Hit.bBlockingHit)
//	//	{
//	//		// We hit something, move there
//	//		SetNewMoveDestination(Hit.ImpactPoint);
//	//	}
//	//}
//}
//
//void ARTS_LessonsPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	FVector2D ScreenSpaceLocation(Location);
//
//	// Trace to see what is under the touch location
//	FHitResult HitResult;
//	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
//	if (HitResult.bBlockingHit)
//	{
//		// We hit something, move there
//		SetNewMoveDestination(HitResult.ImpactPoint);
//	}
//}
//
//void ARTS_LessonsPlayerController::SetNewMoveDestination(const FVector DestLocation)
//{
//	APawn* const MyPawn = GetPawn();
//	if (MyPawn)
//	{
//		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
//
//		// We need to issue move command only if far enough in order for walk animation to play correctly
//		if ((Distance > 120.0f))
//		{
//			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
//		}
//	}
//}


//void ARTS_LessonsPlayerController::OnSetDestinationPressed()
//{
//	// set flag to keep updating destination until released
//	bMoveToMouseCursor = true;
//}
//
//void ARTS_LessonsPlayerController::OnSetDestinationReleased()
//{
//	// clear flag to indicate we should stop updating the destination
//	bMoveToMouseCursor = false;
//}
