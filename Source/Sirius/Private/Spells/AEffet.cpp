// Fill out your copyright notice in the Description page of Project Settings.

#include "Spells/AEffet.h"

// Sets default values
AAEffet::AAEffet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Type = EIngredientType::Effet;

    EffectDictionary.Add(EEffet::Avance, AMoveForward::StaticClass());
}

// Called when the game starts or when spawned
void AAEffet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAEffet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ADefaultEffect* AAEffet::GetEffect()
{
    if (EffectDictionary.Contains(Effet))
    {
        TSubclassOf<ADefaultEffect> EffectClass = EffectDictionary[Effet];
        if (EffectClass)
        {
            ADefaultEffect* EffectInstance = NewObject<ADefaultEffect>(this, EffectClass);
            return EffectInstance;
        }
    }
    return nullptr;
}
