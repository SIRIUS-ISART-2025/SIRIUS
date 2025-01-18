// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/AForme.h"

// Sets default values
AAForme::AAForme()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Type = EIngredientType::Forme;
}

// Called when the game starts or when spawned
void AAForme::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAForme::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

