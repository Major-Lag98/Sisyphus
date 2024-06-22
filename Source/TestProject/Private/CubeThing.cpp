// Fill out your copyright notice in the Description page of Project Settings.
/*
Desription:
Figure out how to move a object(actor).
*/

#include "CubeThing.h"

ACubeThing::ACubeThing()
{
	PrimaryActorTick.bCanEverTick = true;
}

// tick is called every frame with delta seconds parameter
void ACubeThing::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	
	// get the actor locaton
	FVector currentLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	// modify the location
	FVector newLocation = currentLocation + FVector::UpVector;
	// Set the new location back to the actor
	SetActorLocation(newLocation);
}
