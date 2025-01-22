// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "Spells/Effects/DefaultEffect.h"
#include "AForme.h"
#include "AEffet.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TArray<AAForme*> FormesListe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TArray<AAElement*> ElementsListe;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TArray<AAEffet*> EffetsListe;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bTrigerred;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	UStaticMeshComponent* SpellMeshBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	UStaticMeshComponent* SpellMeshTrans;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	ADefaultEffect* EffectInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	ADefaultEffect* EndEffectInstance;

	UPROPERTY(EditAnywhere, Category = "Spell")
	UNiagaraSystem* Particles;

	UPROPERTY(VisibleAnywhere, Category = "Spell")
	float EffectDuration;
	UPROPERTY(VisibleAnywhere, Category = "Spell")
	float TimeElapsed;

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void ApplySpell();

	UFUNCTION(BlueprintCallable, Category = "Spell")
	void BlendMaterials(UStaticMeshComponent* MeshComponent, UMaterialInstance* MaterialParent, UMaterialInstance* ElementMaterial, UTexture2D* BlendTexture);

};
