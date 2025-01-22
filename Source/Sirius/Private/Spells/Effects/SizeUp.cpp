// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/SizeUp.h"

ASizeUp::ASizeUp()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    bShouldBeTriggeredOnceTimeOnly = false;
}

// Called when the game starts or when spawned
void ASizeUp::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASizeUp::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ASizeUp::ApplyEffect(AActor* Target)
{
    if (Target)
    {
        FVector CurrentScale = Target->GetActorScale3D();

        FVector NewScale = CurrentScale * 1.01f; 

        Target->SetActorScale3D(NewScale);
    }
}
