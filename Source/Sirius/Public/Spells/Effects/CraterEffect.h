// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CraterMaker.h"
#include "Spells/Effects/DefaultEffect.h"
#include "CraterEffect.generated.h"

/**
 * 
 */
UCLASS()
class SIRIUS_API ACraterEffect : public ADefaultEffect
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACraterEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ApplyEffect(AActor* Target) override;
};