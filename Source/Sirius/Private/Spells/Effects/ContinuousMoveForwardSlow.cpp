// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/ContinuousMoveForwardSlow.h"

// Sets default values
AContinuousMoveForwardSlow::AContinuousMoveForwardSlow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AContinuousMoveForwardSlow::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AContinuousMoveForwardSlow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AContinuousMoveForwardSlow::ApplyEffect(AActor* Target)
{
	if (Target)
	{
		FVector ForwardDirection = Target->GetActorForwardVector();
		Target->SetActorLocation(Target->GetActorLocation() + ForwardDirection * 1000 * GetWorld()->DeltaTimeSeconds);
	}
}