// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "AElement.generated.h"

UCLASS()
class SIRIUS_API AAElement : public AIngredient
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAElement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "SpellDataElements")
	TObjectPtr<UMaterialInstance> ElementMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SpellDataElements")
	UMaterialInstance* GetMaterial() const { return ElementMaterial; }
};
