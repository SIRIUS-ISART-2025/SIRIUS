// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "AForme.generated.h"

UCLASS()
class SIRIUS_API AAForme : public AIngredient
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAForme();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SpellDataShape")
	UStaticMesh* ShapeMesh;

	UPROPERTY(EditAnywhere, Category = "SpellDataShape")
	TObjectPtr<UMaterialInstance> ShapeMaterial;

	UPROPERTY(EditAnywhere, Category = "SpellDataShape")
	UTexture2D* BlendTexture;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SpellDataShape")
	UStaticMesh* GetMesh() const { return ShapeMesh; }

	UFUNCTION(BlueprintCallable, Category = "SpellDataShape")
	UMaterialInstance* GetMaterial() const { return ShapeMaterial; }

	UFUNCTION(BlueprintCallable, Category = "SpellDataShape")
	UTexture2D* GetBlendTexture() const { return BlendTexture; }
};
