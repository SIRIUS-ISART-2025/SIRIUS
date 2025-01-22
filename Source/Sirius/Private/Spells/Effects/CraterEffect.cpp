// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/CraterEffect.h"

ACraterEffect::ACraterEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACraterEffect::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACraterEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACraterEffect::ApplyEffect(AActor* Target)
{
	if (Target)
	{
		FVector worldLocation = Target->GetActorLocation();
		float adjustRadius = FMath::RandRange(300.f, 500.f);
		float edgeBlendFactor = 1.f;
		float depth = -1 * FMath::RandRange(300.f, 600.f);
		ACraterMaker::SelfSelfCrater->AdjustLandscapeAtWorldLocation(worldLocation, adjustRadius, edgeBlendFactor, depth);
		Target->Destroy();
	}
}