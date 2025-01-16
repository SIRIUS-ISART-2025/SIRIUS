// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Ingredient.h"

// Sets default values
AIngredient::AIngredient()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Initialisation du mesh
    IngredientMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IngredientMesh"));
    RootComponent = IngredientMesh;

    // Activer la physique par défaut
    IngredientMesh->SetSimulatePhysics(true);
    IngredientMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
}

// Called when the game starts or when spawned
void AIngredient::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIngredient::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIngredient::EnablePhysics(bool bSimulate)
{
    if (IngredientMesh)
    {
        IngredientMesh->SetSimulatePhysics(bSimulate);
    }
}