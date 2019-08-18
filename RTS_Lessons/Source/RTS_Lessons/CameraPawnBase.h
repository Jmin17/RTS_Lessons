// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
//#include <fstream>
#include "CameraPawnBase.generated.h"


UCLASS()
class RTS_LESSONS_API ACameraPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UFloatingPawnMovement* floatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UCameraComponent* camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* rootSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USpringArmComponent* springArm;

	//---zooming section----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zooming")
		float minZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zooming")
		float maxZoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zooming")
		float zoomIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float cameraDistance;

	bool zooming;
	float desiredMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zooming")
	float zoomSmoothingGradient;

	//std::ofstream myFile;

public:	

	void MoveForward(float amount);
	void MoveRight(float amount);
	void ZoomIn();
	void ZoomOut();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
