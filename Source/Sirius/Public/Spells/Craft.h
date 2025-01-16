// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ingredient.h"
#include "../Staff.h"
#include "Components/BoxComponent.h"
#include "Craft.generated.h"

UCLASS()
class SIRIUS_API ACraft : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACraft();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void AddIngredient(AIngredient* Ingredient);
    void ResetMachine();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // Zone de détection
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* DetectionZone;

    // Mesh de la machine
    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* MachineMesh;

    // Enums pour le résultat final
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EElement ResultElement;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EForme ResultForme;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    EEffet ResultEffet;

    // Booléens pour vérifier si un type a été ajouté
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    bool bHasElement;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    bool bHasForme;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    bool bHasEffet;

    // Fonction appelée lorsque quelque chose entre dans la zone
    UFUNCTION()
    void OnIngredientDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Craft")
    TSubclassOf<AStaff> StaffBlueprint; 

    UPROPERTY()
    AStaff* CreatedStaff; 

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Craft|Spawn")
    USceneComponent* StaffSpawnPoint;
};
