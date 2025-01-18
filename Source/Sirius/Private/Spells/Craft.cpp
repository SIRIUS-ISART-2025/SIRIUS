// Fill out your copyright notice in the Description page of Project Settings.

#include "Spells/Craft.h"
#include "Spells/AEffet.h"
#include "Spells/AForme.h"
#include "Spells/AElement.h"

// Sets default values
ACraft::ACraft()
{
	PrimaryActorTick.bCanEverTick = true;

    MachineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MachineMesh"));
    RootComponent = MachineMesh;

    DetectionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionZone"));
    DetectionZone->SetupAttachment(MachineMesh);
    DetectionZone->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    DetectionZone->OnComponentBeginOverlap.AddDynamic(this, &ACraft::OnIngredientDetected);

    StaffSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("StaffSpawnPoint"));
    StaffSpawnPoint->SetupAttachment(RootComponent);

    bHasElement = false;
    bHasForme = false;
    bHasEffet = false;
}

void ACraft::BeginPlay()
{
	Super::BeginPlay();
}

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
                AAElement* ElementIngredient = Cast<AAElement>(Ingredient);
                if (ElementIngredient)
                {
                    ResultElement = ElementIngredient;
                    ResultElementName = Ingredient->Element;
                    bHasElement = true;
                    StoredIngredients.Add(Ingredient);
                    Ingredient->SetActorHiddenInGame(true);
                    Ingredient->SetActorEnableCollision(false);
                    Ingredient->SetActorTickEnabled(false);
                }
            }
            break;
        case EIngredientType::Forme:
            if (!bHasForme)
            {
                AAForme* FormeIngredient = Cast<AAForme>(Ingredient);
                if (FormeIngredient)
                {
                    ResultForme = FormeIngredient;
                    ResultFormeName = Ingredient->Forme;
                    bHasForme = true;
                    StoredIngredients.Add(Ingredient);
                    Ingredient->SetActorHiddenInGame(true);
                    Ingredient->SetActorEnableCollision(false);
                    Ingredient->SetActorTickEnabled(false);
                }
            }
            break;
        case EIngredientType::Effet:
            if (!bHasEffet)
            {   
                AAEffet* EffectIngredient = Cast<AAEffet>(Ingredient);
                if (EffectIngredient)
                {
                    ResultEffet = EffectIngredient;
                    ResultEffetName = Ingredient->Effet;
                    bHasEffet = true;
                    StoredIngredients.Add(Ingredient);
                    Ingredient->SetActorHiddenInGame(true);
                    Ingredient->SetActorEnableCollision(false);
                    Ingredient->SetActorTickEnabled(false);
                }
            }
            break;
    }

    if (bHasElement && bHasForme && bHasEffet)
    {
        if (StaffBlueprint && StaffSpawnPoint)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;

            FVector SpawnLocation = StaffSpawnPoint->GetComponentLocation();
            FRotator SpawnRotation = StaffSpawnPoint->GetComponentRotation();

            CreatedStaff = GetWorld()->SpawnActor<AStaff>(StaffBlueprint, SpawnLocation, SpawnRotation, SpawnParams);

            if (CreatedStaff)
            {
                CreatedStaff->SetResults(ResultElementName, ResultFormeName, ResultEffetName, ResultElement, ResultForme, ResultEffet);
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

    ResultElementName = EElement::Feu;
    ResultFormeName = EForme::Arbre;
    ResultEffetName = EEffet::Immobile;
}