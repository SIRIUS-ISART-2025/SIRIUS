// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ingredient.generated.h"

UENUM(BlueprintType)
enum class EIngredientType : uint8
{
    Element UMETA(DisplayName = "Element"),
    Forme UMETA(DisplayName = "Forme"),
    Effet UMETA(DisplayName = "Effet")
};

UENUM(BlueprintType)
enum class EElement : uint8
{
    Feu UMETA(DisplayName = "Feu"),
    Soap UMETA(DisplayName = "Savon"),
    Thunder UMETA(DisplayName = "Foudre"),
    Cheese UMETA(DisplayName = "Fromage"),
    Crystal UMETA(DisplayName = "Crystal")
};

UENUM(BlueprintType)
enum class EForme : uint8
{
    Arbre UMETA(DisplayName = "Arbre"),
    Poule UMETA(DisplayName = "Poule"),
    Sphere UMETA(DisplayName = "Sphere"),
    Skull UMETA(DisplayName = "Crane"),
    Cadre UMETA(DisplayName = "Cadre"),
    Fountain UMETA(DisplayName = "Fontaine"),
    Cone UMETA(DisplayName = "Cone"),
    Cube UMETA(DisplayName = "Cube")
};

UENUM(BlueprintType)
enum class EEffet : uint8
{
    Immobile UMETA(DisplayName = "Immobile"),
    Avance UMETA(DisplayName = "Avance"),
    AvanceLentement UMETA(DisplayName = "AvanceLentement"),
    Chaotic UMETA(DisplayName = "Chaotic"),
    Grossi UMETA(DisplayName = "Grossi"),
    Rapetissi UMETA(DisplayName = "Rapetissi")
};

UCLASS()
class SIRIUS_API AIngredient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIngredient();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* IngredientMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EIngredientType Type;

    // Valeurs spécifiques pour chaque type
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EElement Element;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EForme Forme;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEffet Effet;

    void EnablePhysics(bool bSimulate);
};
