// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

class UInputAction;
class UInputMappingContext;


UCLASS()
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PawnClientRestart() override;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> InteractWidgetClass;
	UPROPERTY()
	UUserWidget* InteractWidget;

private:
	// functions for locomotion
	// move the character
	void Move(const FInputActionValue& ActionValue);
	// look around
	void Look(const FInputActionValue& ActionVelue);
	// jump
	void Jump(const FInputActionValue& ActionValue);

	void Interact();
	void InteractCheck();

	FHitResult InteractHitResult;
	FVector ViewVector;
	FRotator ViewRotation;

};
