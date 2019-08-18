// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawnBase.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/SceneComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
//#include "Classes/Engine/World.h"
//#include "Classes/GameFramework/PlayerController.h"
//#include "Classes/Kismet/GameplayStatics.h"
//#include "Runtime/InputCore/Classes/InputCoreTypes.h"
//#include <fstream>
//#include <iostream>


// Sets default values
ACameraPawnBase::ACameraPawnBase()
{

	PrimaryActorTick.bCanEverTick = true;// draws/updates pawn every frame, can be false to not do that

	
	//initializing a root component for other components to attach to,
	//multi-component objects all need to have a root component
	rootSceneComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	//creating a spring arm which will hold the camera at a certain distance back
	// and above to enable a good view
	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	springArm->SetupAttachment(rootSceneComponent);
	//causes the camera to be up at an angle looking down
	springArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	minZoom = 300.f;
	maxZoom = 3000.f;
	zoomIncrement = 100.f;
	zoomSmoothingGradient = 8.f;
	cameraDistance = 800.f;
	springArm->TargetArmLength = cameraDistance;// how far away the camera is
	springArm->bDoCollisionTest = false;
	zooming = false;

	// smooths camera movement to prevent jerkiness, especially helpful on 
	// zooming the camera in and out
	//springArm->bEnableCameraLag = true;
	//springArm->CameraLagSpeed = 5.0f;

	//used for binding the pawn's movement to player inputs
	floatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");
	
	// this creates the camera
	camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	// the line below is not necessary as it was covered by adding the spring arm
	//camera->SetRelativeLocationAndRotation(FVector(-500.f, 0.f, -500.f), FRotator(-60.f, 0.f, 0.f));
	// attaching the camera to the spring arm
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	
	floatingPawnMovement->Acceleration = 20000.0f;
	floatingPawnMovement->Deceleration = 20000.0f;
	floatingPawnMovement->MaxSpeed = 4500.0f;
	floatingPawnMovement->TurningBoost = 30.0f;
	
	// doesn't work
	// gives the pawn a handle to the player controller
	//playerController = GetWorld()->GetFirstPlayerController();
	//playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	//{
	//	using namespace std;
	//	myFile.open("johnny.txt");
	//	if (playerController != nullptr)
	//	{
	//		myFile << "Success!";

	//	}
	//	else
	//	{
	//		myFile << "Failure :(" << endl << endl;
	//	}
	//	myFile.close();
	//}//namespace std

	//this causes the player to automatically "possess" this pawn
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACameraPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraPawnBase::MoveForward(float amount)
{
	floatingPawnMovement->AddInputVector(GetActorForwardVector() * amount);
}

void ACameraPawnBase::MoveRight(float amount)
{
	floatingPawnMovement->AddInputVector(GetActorRightVector() * amount);
}

void ACameraPawnBase::ZoomIn()
{
	if (cameraDistance > minZoom)
		cameraDistance -= zoomIncrement;

	zooming = true;
	//springArm->TargetArmLength = cameraDistance;

}

void ACameraPawnBase::ZoomOut()
{
	if (cameraDistance < maxZoom)
		cameraDistance += zoomIncrement;

	zooming = true;
	//springArm->TargetArmLength = cameraDistance;

}

// Called every frame
void ACameraPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// applying a smoothing function to the change in zoom
	if (zooming)
	{
		if (springArm->TargetArmLength != cameraDistance)
		{
			desiredMovement = (cameraDistance - springArm->TargetArmLength)/zoomSmoothingGradient;

			if (abs(desiredMovement) < 1 )
			{
				desiredMovement = cameraDistance - springArm->TargetArmLength;
			}

			springArm->TargetArmLength += desiredMovement;
		}
		else
		{
			zooming = false;
		}
	}//end if


}

// Called to bind functionality to input
void ACameraPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &ACameraPawnBase::ZoomIn);
	PlayerInputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &ACameraPawnBase::ZoomOut);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACameraPawnBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACameraPawnBase::MoveRight);
	
	
	//FVector direction = 

}

