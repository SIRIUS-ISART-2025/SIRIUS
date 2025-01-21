// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "Spells/Effects/DefaultEffect.h"
#include "Spells/Effects/MoveForward.h"
#include "AEffet.generated.h"

UCLASS()
class SIRIUS_API AAEffet : public AIngredient
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAEffet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Effet")
	ADefaultEffect* GetEffect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effet") 
	TMap<EEffet, TSubclassOf<ADefaultEffect>> EffectDictionary;
};
