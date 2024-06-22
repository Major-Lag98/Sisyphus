// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CubeThing.generated.h"

/**
 * 
 */
UCLASS()
class ACubeThing : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ACubeThing();
	virtual void Tick(float deltaSeconds) override;
};
