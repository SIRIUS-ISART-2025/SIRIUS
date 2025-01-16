// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Landscape.h"
#include "LandscapeComponent.h"
#include "LandscapeEdit.h"

#include "CraterMaker.generated.h"

UCLASS()
class SIRIUS_API ACraterMaker : public AActor
{
	GENERATED_BODY()

private:
	ALandscape* landscape;
	
public:	
	// Sets default values for this actor's properties
	ACraterMaker();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "CraterParameter")
	FVector worldLocation = {0,0,-1768};
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "CraterParameter")
	float adjustRadius = 3000;
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "CraterParameter")
	float edgeBlendFactor = 1;

	void AdjustLandscapeAtWorldLocation(const FVector& WorldLocation, float AdjustRadius, float EdgeBlendFactor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnPKeyPressed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
