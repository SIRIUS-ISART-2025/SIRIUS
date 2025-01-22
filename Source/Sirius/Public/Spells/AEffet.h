// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spells/Ingredient.h"
#include "Spells/Effects/DefaultEffect.h"
#include "Spells/Effects/MoveForward.h"
#include "AEffet.generated.h"

UENUM(BlueprintType)
enum class EEndEffet : uint8
{
	DestroySelf UMETA(DisplayName = "DestroySelf"),
	CraterDestroy UMETA(DisplayName = "CraterDestroy")
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effet")
	EEndEffet EndEffet;

	UFUNCTION(BlueprintCallable, Category = "Effet")
	ADefaultEffect* GetEffect();

	UFUNCTION(BlueprintCallable, Category = "Effet")
	ADefaultEffect* GetEndEffect();

	UPROPERTY(EditAnywhere, Category = "Effet")
	float EffectDuration = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effet") 
	TMap<EEffet, TSubclassOf<ADefaultEffect>> EffectDictionary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effet")
	TMap<EEndEffet, TSubclassOf<ADefaultEffect>> EndEffectDictionary;

	UFUNCTION(BlueprintCallable, Category = "Effet")
	float GetEffectDuration() const { return EffectDuration;  };
};
