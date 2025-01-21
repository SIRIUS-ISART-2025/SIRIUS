// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "Spells/Effects/DefaultEffect.h"
#include "AForme.h"
#include "AEffet.h"
#include "AElement.h"
#include "Spell.generated.h"

UCLASS()
class SIRIUS_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpell();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	AAForme* Forme;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	AAElement* Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	AAEffet* Effet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	UStaticMeshComponent* SpellMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	ADefaultEffect* EffectInstance;

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void ApplySpell();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void BlendMaterials(UStaticMeshComponent* MeshComponent, UMaterialInstance* MaterialParent, UMaterialInstance* ElementMaterial, UTexture2D* BlendTexture);

};
