// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/AElement.h"

// Sets default values
AAElement::AAElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Type = EIngredientType::Element;
}

// Called when the game starts or when spawned
void AAElement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

