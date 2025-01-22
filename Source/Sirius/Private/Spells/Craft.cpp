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
    bHasStaff = false;
}

void ACraft::BeginPlay()
{
	Super::BeginPlay();
    GEngine->ForceGarbageCollection(false);
}

void ACraft::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACraft::OnIngredientDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    AIngredient* Ingredient_ = Cast<AIngredient>(OtherActor);
    if (Ingredient_)
    {
        AddIngredient(Ingredient_);
    }

    AStaff* Staff_ = Cast<AStaff>(OtherActor);
    if (Staff_)
    {
        AddStaff(Staff_);
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

void ACraft::AddStaff(AStaff* Staff)
{
    if (!bHasStaff) 
    {
        ResultStaff = Staff;
        Staff->SetActorHiddenInGame(true);
        Staff->SetActorEnableCollision(false);
        Staff->SetActorTickEnabled(false);
        bHasStaff = true;
    } else 
    {
        Staff->FormesListe.Add(ResultStaff->ResultForme);
        Staff->ElementsListe.Add(ResultStaff->ResultElement);
        Staff->EffetsListe.Add(ResultStaff->ResultEffet);

        if (ResultStaff->FormesListe.Num() > 0 && ResultStaff->ElementsListe.Num() > 0 && ResultStaff->EffetsListe.Num() > 0)
        {
            for (int32 i = 0; i < ResultStaff->FormesListe.Num(); ++i)
            {
                Staff->FormesListe.Add(ResultStaff->FormesListe[i]);
                Staff->ElementsListe.Add(ResultStaff->ElementsListe[i]);
                Staff->EffetsListe.Add(ResultStaff->EffetsListe[i]);
            }
        }

        if (Staff && Staff->GetMesh())
        {
            FVector Impulse = FVector(0, 0, 1) * 300.0f;
            FVector ImpulseLocation = GetActorLocation();

            Staff->GetMesh()->AddImpulseAtLocation(Impulse, ImpulseLocation);
        }

        bHasStaff = false;
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