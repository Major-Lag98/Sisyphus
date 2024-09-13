// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Item.h"

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

	InteractCheck();
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
		if (InteractAction)
		{
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacter::Interact);
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

void AMyCharacter::InteractCheck()
{
	Cast<APlayerController>(GetController())->GetPlayerViewPoint(ViewVector, ViewRotation);
	FVector VecDirection = ViewRotation.Vector() * 1000.f; // Get direction of view
	FVector InteractEnd = ViewVector + VecDirection; // Set start and end
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(InteractHitResult, ViewVector, InteractEnd, ECollisionChannel::ECC_GameTraceChannel1, QueryParams);
}

void AMyCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Casting line trace..."));

	// Get the view vector and rotation for line trace debug
	Cast<APlayerController>(GetController())->GetPlayerViewPoint(ViewVector, ViewRotation);
	FVector VecDirection = ViewRotation.Vector() * 1000.f; // Get direction of view
	FVector InteractEnd = ViewVector + VecDirection;

	// Draw a line showing the direction of the view
	DrawDebugLine(GetWorld(), ViewVector, InteractEnd, FColor::Red, false, 5, 0, 1);

	// If we hit a AItem class, do stuff
	if (Cast<AItem>(InteractHitResult.GetActor())) 
	{
		// Show the name of item hit as it shows in the outliner
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *InteractHitResult.GetActor()->GetName());
	}
}

