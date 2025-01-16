// Fill out your copyright notice in the Description page of Project Settings.


#include "Staff.h"

// Sets default values
AStaff::AStaff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Initialisation du mesh
    StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaffMesh"));
    RootComponent = StaffMesh;

    // Configuration de la collision pour le bâton
    StaffMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
    StaffMesh->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void AStaff::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaff::SetResults(EElement Element, EForme Forme, EEffet Effet)
{
    ResultElement = Element;
    ResultForme = Forme;
    ResultEffet = Effet;
}

void AStaff::LogResults()
{
    UE_LOG(LogTemp, Warning, TEXT("Element: %s, Forme: %s, Effet: %s"),
        *UEnum::GetValueAsString(ResultElement),
        *UEnum::GetValueAsString(ResultForme),
        *UEnum::GetValueAsString(ResultEffet));
}

void AStaff::StartFloating()
{
    GetWorldTimerManager().SetTimer(
        FloatingTimerHandle,
        this,
        &AStaff::HandleFloating,
        0.016f,
        true
    );
}

void AStaff::HandleFloating()
{
    FVector NewLocation = GetActorLocation();
    float DeltaTime = GetWorld()->GetDeltaSeconds();

    // Mouvement de flottement (sinusoïdal)
    NewLocation.Z += FMath::Sin(GetWorld()->TimeSeconds * FloatFrequency) * FloatAmplitude * DeltaTime;
    SetActorLocation(NewLocation);
}   