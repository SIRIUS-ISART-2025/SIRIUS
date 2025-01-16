// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "Staff.generated.h"

UCLASS()
class SIRIUS_API AStaff : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStaff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // Mesh pour le bâton
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* StaffMesh;

    // Les trois enums résultants
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EElement ResultElement;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EForme ResultForme;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEffet ResultEffet;

    // Définir les valeurs des résultats
    void SetResults(EElement Element, EForme Forme, EEffet Effet);

    // Afficher les valeurs des résultats dans les logs
    void LogResults();

    UFUNCTION()
    void StartFloating();

    UFUNCTION()
    void HandleFloating();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff|Animation")
    float FloatSpeed = 20.0f; // Vitesse de montée initiale

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff|Animation")
    float FloatAmplitude = 10.0f; // Amplitude du flottement

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Staff|Animation")
    float FloatFrequency = 1.0f; // Fréquence du flottement

    UPROPERTY()
    FTimerHandle FloatingTimerHandle;

};
