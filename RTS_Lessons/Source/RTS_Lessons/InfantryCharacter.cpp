// Fill out your copyright notice in the Description page of Project Settings.


#include "InfantryCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"
#include "Engine.h"
#include "EngineGlobals.h"

// Sets default values
AInfantryCharacter::AInfantryCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);


	MeshLocation = FVector(0.f, 0.f, -80.f);
	this->GetMesh()->SetRelativeLocation(MeshLocation);
	
	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// IUnit Interface
	this->bSelected = false;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

// Called when the game starts or when spawned
void AInfantryCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInfantryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AInfantryCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindKey(EKeys::LeftShift,IE_Pressed, this,&AInfantryCharacter::)
}

//IUnit Interface
bool AInfantryCharacter::IsSelected_Implementation()
{
	return this->bSelected;
}

//IUnit Interface
void AInfantryCharacter::Select_Implementation()
{
	bSelected = !bSelected;
	if (GEngine)
	{
		FString myString = bSelected ? TEXT("Selected ") : TEXT("Deselected ");
		myString.Append(this->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, myString);
	}
}

