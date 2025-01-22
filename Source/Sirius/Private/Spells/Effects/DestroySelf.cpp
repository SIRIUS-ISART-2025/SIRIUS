// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/DestroySelf.h"

ADestroySelf::ADestroySelf()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestroySelf::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ADestroySelf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestroySelf::ApplyEffect(AActor* Target)
{
	if (Target)
	{
		Target->Destroy();
	}
}