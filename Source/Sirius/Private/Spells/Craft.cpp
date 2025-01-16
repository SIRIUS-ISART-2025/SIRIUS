// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Craft.h"

// Sets default values
ACraft::ACraft()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Initialisation du mesh
    MachineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineMesh"));
    RootComponent = MachineMesh;

    // Initialisation de la zone de détection
    DetectionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionZone"));
    DetectionZone->SetupAttachment(MachineMesh);
    DetectionZone->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    DetectionZone->OnComponentBeginOverlap.AddDynamic(this, &ACraft::OnIngredientDetected);

    StaffSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("StaffSpawnPoint"));
    StaffSpawnPoint->SetupAttachment(RootComponent);

    // Initialisation des états
    bHasElement = false;
    bHasForme = false;
    bHasEffet = false;
}

// Called when the game starts or when spawned
void ACraft::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraft::OnIngredientDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    AIngredient* Ingredient = Cast<AIngredient>(OtherActor);
    if (Ingredient)
    {
        AddIngredient(Ingredient);
    }
}

void ACraft::AddIngredient(AIngredient* Ingredient)
{
    switch (Ingredient->Type)
    {
    case EIngredientType::Element:
        if (!bHasElement)
        {
            ResultElement = Ingredient->Element;
            bHasElement = true;
            Ingredient->Destroy(); // Supprime l'ingrédient
        }
        break;
    case EIngredientType::Forme:
        if (!bHasForme)
        {
            ResultForme = Ingredient->Forme;
            bHasForme = true;
            Ingredient->Destroy();
        }
        break;
    case EIngredientType::Effet:
        if (!bHasEffet)
        {
            ResultEffet = Ingredient->Effet;
            bHasEffet = true;
            Ingredient->Destroy();
        }
        break;
    }

    if (bHasElement && bHasForme && bHasEffet)
    {
        if (StaffBlueprint && StaffSpawnPoint)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;

            // Utiliser la position du StaffSpawnPoint
            FVector SpawnLocation = StaffSpawnPoint->GetComponentLocation();
            FRotator SpawnRotation = StaffSpawnPoint->GetComponentRotation();

            // Spawner le bâton
            CreatedStaff = GetWorld()->SpawnActor<AStaff>(StaffBlueprint, SpawnLocation, SpawnRotation, SpawnParams);

            if (CreatedStaff)
            {
                CreatedStaff->SetResults(ResultElement, ResultForme, ResultEffet);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Cannot spawn staff! StaffBlueprint or StaffSpawnPoint is not set."));
        }

        ResetMachine();
    }
}

void ACraft::ResetMachine()
{
    bHasElement = false;
    bHasForme = false;
    bHasEffet = false;

    ResultElement = EElement::Feu;
    ResultForme = EForme::Arbre;
    ResultEffet = EEffet::Immobile;
}