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

	SpellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpellMesh"));
	SpellMesh->SetSimulatePhysics(true);
	SpellMesh->SetEnableGravity(true);
	SpellMesh->SetCollisionProfileName(TEXT("PhysicsActor"));

	RootComponent = SpellMesh;
}


void ASpell::BeginPlay()
{
	Super::BeginPlay();

	if (Forme && Effet && Element)
	{
		ApplySpell();
	}
}

void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EffectInstance)
	{
		EffectInstance->ApplyEffect(this);
	}
}

void ASpell::ApplySpell()
{
	if (Forme)
	{
		SpellMesh->SetStaticMesh(Forme->GetMesh());
	}

	if (Element && Forme)
	{
        UMaterialInstance* Material = Element->GetMaterial();
		if (Material)
		{
			SpellMesh->SetMaterial(0, Material);
            UE_LOG(LogTemp, Warning, TEXT("BlendMaterials"));
			//BlendMaterials(SpellMesh, Forme->GetMaterial(), Material, Forme->GetBlendTexture());
		}
	} else 
    {
        UE_LOG(LogTemp, Warning, TEXT("Element && Forme fail"));
    }

	if (Effet)
	{
		EffectInstance = Effet->GetEffect();
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

    // Créer un matériau dynamique pour le blending
    UMaterialInstanceDynamic* BlendedMaterial = UMaterialInstanceDynamic::Create(MaterialParent, this);
    if (!BlendedMaterial)
    {
        UE_LOG(LogTemp, Error, TEXT("BlendMaterials: Failed to create dynamic material instance."));
        return;
    }

    // Récupération des paramètres des deux matériaux
    FLinearColor BaseColorA = FLinearColor::White;
    FLinearColor BaseColorB = FLinearColor::White;

    float MetallicA = 0.0f;
    float MetallicB = 0.0f;

    float RoughnessA = 0.5f;
    float RoughnessB = 0.5f;

    // Récupération des valeurs via GetScalar/VectorParameter
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

    // Configurer les paramètres interpolés dans le matériau blendé
    BlendedMaterial->SetVectorParameterValue(FName("BaseColor_A"), BaseColorA);
    BlendedMaterial->SetVectorParameterValue(FName("BaseColor_B"), BaseColorB);

    BlendedMaterial->SetScalarParameterValue(FName("Metallic_A"), MetallicA);
    BlendedMaterial->SetScalarParameterValue(FName("Metallic_B"), MetallicB);

    BlendedMaterial->SetScalarParameterValue(FName("Roughness_A"), RoughnessA);
    BlendedMaterial->SetScalarParameterValue(FName("Roughness_B"), RoughnessB);

    // Ajouter la texture de blending
    BlendedMaterial->SetTextureParameterValue(FName("BlendTexture"), BlendTexture);

    // Optionnel : Configurer un BlendAlpha pour modifier l'intensité du mélange
    BlendedMaterial->SetScalarParameterValue(FName("BlendAlpha"), 0.5f);

    // Appliquer le matériau blendé au mesh
    MeshComponent->SetMaterial(0, BlendedMaterial);
}
