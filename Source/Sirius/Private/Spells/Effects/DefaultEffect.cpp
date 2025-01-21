// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/DefaultEffect.h"

// Sets default values
ADefaultEffect::ADefaultEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADefaultEffect::ApplyEffect(AActor* Target)
{
	// TO DO IN CHILDS
}
