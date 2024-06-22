// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		if (MoveAction)
		{
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		}
		if (LookAction)
		{
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		}
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyCharacter::Jump);
		}
	}

}

void AMyCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = Cast<APlayerController>(GetController())->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
	{
		Subsystem->ClearAllMappings();

		Subsystem->AddMappingContext(MappingContext, 0);
	}
}

void AMyCharacter::Move(const FInputActionValue& ActionValue)
{
	// get the movement input value and add it to the character
	AddMovementInput(GetActorForwardVector(), ActionValue[0]);
	AddMovementInput(GetActorRightVector(), ActionValue[1]);
}

void AMyCharacter::Look(const FInputActionValue& ActionValue)
{
	const FVector2D LookAxisValue = ActionValue.Get<FVector2D>();
	if(GetController())
	{
		// add the pitch and yaw input
		AddControllerPitchInput(LookAxisValue.Y);
		AddControllerYawInput(LookAxisValue.X);
	}
}

void AMyCharacter::Jump(const FInputActionValue& ActionValue)
{
    if (ActionValue[0])
    {
        // Add an impulse upward to the character
        ACharacter::Jump();
    }
}



