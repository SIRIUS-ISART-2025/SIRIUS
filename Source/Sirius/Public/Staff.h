#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Effects/DefaultEffect.h"
#include "Spells/Spell.h"
#include "Spells/Ingredient.h"
#include "Staff.generated.h"

UCLASS()
class SIRIUS_API AStaff : public AActor
{
	GENERATED_BODY()
	
public:	
	AStaff();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

    // Mesh pour le bâton
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaffMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AAElement* ResultElement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AAForme* ResultForme;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    AAEffet* ResultEffet;

    // Les trois enums résultants
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EElement ResultElementName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EForme ResultFormeName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEffet ResultEffetName;

    // Les fonctions de creation de sort
    UFUNCTION()
    void SetResults(EElement ElementName, EForme FormeName, EEffet EffetName, AAElement* ResultElement_, AAForme* ResultForme_, AAEffet* ResultEffet_);

    UFUNCTION()
    void LogResults();
};