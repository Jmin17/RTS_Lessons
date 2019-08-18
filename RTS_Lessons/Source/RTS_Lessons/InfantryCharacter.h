// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.h"
#include "InfantryCharacter.generated.h"

UCLASS(Blueprintable)
class RTS_LESSONS_API AInfantryCharacter : public ACharacter, public IUnit
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AInfantryCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Unit")
	bool IsSelected();
	virtual bool IsSelected_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Unit")
		void Select();
	virtual void Select_Implementation() override;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	FVector MeshLocation;
};
