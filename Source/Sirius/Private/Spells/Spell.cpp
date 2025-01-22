// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Spell.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Texture.h"
#include "Spells/MaterialBlendUtility.h"
#include "Spells/Effects/DefaultEffect.h" 

ASpell::ASpell()
{
	PrimaryActorTick.bCanEverTick = true;

    SpellMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpellMeshBase"));
    SpellMeshBase->SetSimulatePhysics(true);
    SpellMeshBase->SetEnableGravity(true);
    SpellMeshBase->SetCollisionProfileName(TEXT("PhysicsActor"));

    SpellMeshTrans = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpellMeshTrans"));

	RootComponent = SpellMeshBase;
    SpellMeshTrans->SetupAttachment(SpellMeshBase);

    EffectDuration = 0.0f;
    TimeElapsed = 0.0f;
    bTrigerred = false;
}


void ASpell::BeginPlay()
{
	Super::BeginPlay();

    EffectDuration = FMath::RandRange(5.0f, 15.0f);
    TimeElapsed = 0.0f;

	if (Forme && Effet && Element)
	{
		ApplySpell();
	}
}

void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (TimeElapsed < EffectDuration)
    {
        if (EffectInstance)
        {
            if ((EffectInstance->bShouldBeTriggeredOnceTimeOnly && !bTrigerred) || (!EffectInstance->bShouldBeTriggeredOnceTimeOnly))
            {
                EffectInstance->ApplyEffect(this);
                bTrigerred = true;
            }
            TimeElapsed += DeltaTime;
        }
    }
    else 
    {
        if (FormesListe.Num() > 0 && ElementsListe.Num() > 0 && EffetsListe.Num() > 0)
        {
            // Obtenez un nombre al�atoire entre 1 et 15
            int32 NumSpellsToSpawn = FMath::RandRange(1, 15);

            for (int32 j = 0; j < NumSpellsToSpawn; ++j)
            {
                FVector SpawnLocation = GetActorLocation();
                FRotator SpawnRotation = GetActorRotation();

                // Faites spawn un sort
                ASpell* SpawnedSpell = GetWorld()->SpawnActor<ASpell>(ASpell::StaticClass(), SpawnLocation, SpawnRotation);

                if (SpawnedSpell)
                {
                    // Assignez les valeurs des listes au premier sort
                    SpawnedSpell->Forme = FormesListe[0];
                    SpawnedSpell->Element = ElementsListe[0];
                    SpawnedSpell->Effet = EffetsListe[0];

                    // Appliquez le sort
                    SpawnedSpell->ApplySpell();

                    // Ajoutez les autres �l�ments des listes au sort
                    for (int32 i = 1; i < FormesListe.Num(); ++i)
                    {
                        SpawnedSpell->FormesListe.Add(FormesListe[i]);
                        SpawnedSpell->ElementsListe.Add(ElementsListe[i]);
                        SpawnedSpell->EffetsListe.Add(EffetsListe[i]);
                    }
                }
            }
        }


        EndEffectInstance->ApplyEffect(this);
    }
}

void ASpell::ApplySpell()
{
	if (Forme)
	{
        if (Forme->GetMeshBase())
        {
            SpellMeshBase->SetStaticMesh(Forme->GetMeshBase());
        }
        if (Forme->GetMeshTrans())
        {
            SpellMeshTrans->SetStaticMesh(Forme->GetMeshTrans());

            if (Element && Element->GetMaterial())
            {
                SpellMeshBase->SetMaterial(0, Forme->GetMaterial());
                SpellMeshTrans->SetMaterial(0, Element->GetMaterial());

                if (Element->GetParticles())
                {
                    Particles = Element->GetParticles();
                    UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(Particles, SpellMeshTrans, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
                }
            }
        }
        else if (Forme->GetMeshBase()) {
            SpellMeshBase->SetMaterial(0, Element->GetMaterial());

            if (Element->GetParticles())
            {
                Particles = Element->GetParticles();
                UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(Particles, SpellMeshBase, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::Type::KeepRelativeOffset, true);
            }
        }
	}

	if (Effet)
	{
        EffectDuration = Effet->GetEffectDuration();
		EffectInstance = Effet->GetEffect();
        EndEffectInstance = Effet->GetEndEffect();
	}
}

void ASpell::BlendMaterials(UStaticMeshComponent* MeshComponent, UMaterialInstance* MaterialParent, UMaterialInstance* ElementMaterial, UTexture2D* BlendTexture)
{
    UE_LOG(LogTemp, Warning, TEXT("BlendMaterials"));

    if (!MeshComponent || !MaterialParent || !ElementMaterial || !BlendTexture)
    {
        UE_LOG(LogTemp, Warning, TEXT("BlendMaterials: Invalid parameters."));
        return;
    }

    // Cr�er un mat�riau dynamique pour le blending
    UMaterialInstanceDynamic* BlendedMaterial = UMaterialInstanceDynamic::Create(MaterialParent, this);
    if (!BlendedMaterial)
    {
        UE_LOG(LogTemp, Error, TEXT("BlendMaterials: Failed to create dynamic material instance."));
        return;
    }

    // R�cup�ration des param�tres des deux mat�riaux
    FLinearColor BaseColorA = FLinearColor::White;
    FLinearColor BaseColorB = FLinearColor::White;

    float MetallicA = 0.0f;
    float MetallicB = 0.0f;

    float RoughnessA = 0.5f;
    float RoughnessB = 0.5f;

    // R�cup�ration des valeurs via GetScalar/VectorParameter
    if (MaterialParent->GetVectorParameterValue(FName("BaseColor"), BaseColorA))
    {
        UE_LOG(LogTemp, Log, TEXT("BaseColorA: %s"), *BaseColorA.ToString());
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("BlendMaterials: Failed to GetVectorParameterValue BaseColorA."));
    }

    if (ElementMaterial->GetVectorParameterValue(FName("BaseColor"), BaseColorB))
    {
        UE_LOG(LogTemp, Log, TEXT("BaseColorB: %s"), *BaseColorB.ToString());
    } else 
    {
        UE_LOG(LogTemp, Warning, TEXT("BlendMaterials: Failed to GetVectorParameterValue BaseColorB."));
    }

    MaterialParent->GetScalarParameterValue(FName("Metallic"), MetallicA);
    ElementMaterial->GetScalarParameterValue(FName("Metallic"), MetallicB);

    MaterialParent->GetScalarParameterValue(FName("Roughness"), RoughnessA);
    ElementMaterial->GetScalarParameterValue(FName("Roughness"), RoughnessB);

    UE_LOG(LogTemp, Log, TEXT("MetallicA: %f"), MetallicA);
    UE_LOG(LogTemp, Log, TEXT("MetallicB: %f"), MetallicB);
    UE_LOG(LogTemp, Log, TEXT("RoughnessA: %f"), RoughnessA);
    UE_LOG(LogTemp, Log, TEXT("RoughnessB: %f"), RoughnessB);

    // Configurer les param�tres interpol�s dans le mat�riau blend�
    BlendedMaterial->SetVectorParameterValue(FName("BaseColor_A"), BaseColorA);
    BlendedMaterial->SetVectorParameterValue(FName("BaseColor_B"), BaseColorB);

    BlendedMaterial->SetScalarParameterValue(FName("Metallic_A"), MetallicA);
    BlendedMaterial->SetScalarParameterValue(FName("Metallic_B"), MetallicB);

    BlendedMaterial->SetScalarParameterValue(FName("Roughness_A"), RoughnessA);
    BlendedMaterial->SetScalarParameterValue(FName("Roughness_B"), RoughnessB);

    // Ajouter la texture de blending
    BlendedMaterial->SetTextureParameterValue(FName("BlendTexture"), BlendTexture);

    // Optionnel : Configurer un BlendAlpha pour modifier l'intensit� du m�lange
    BlendedMaterial->SetScalarParameterValue(FName("BlendAlpha"), 0.5f);

    // Appliquer le mat�riau blend� au mesh
    MeshComponent->SetMaterial(0, BlendedMaterial);
}
