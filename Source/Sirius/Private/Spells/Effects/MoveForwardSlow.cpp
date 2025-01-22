// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/MoveForwardSlow.h"

AMoveForwardSlow::AMoveForwardSlow()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    bShouldBeTriggeredOnceTimeOnly = false;

}

// Called when the game starts or when spawned
void AMoveForwardSlow::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AMoveForwardSlow::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMoveForwardSlow::ApplyEffect(AActor* Target)
{
    if (Target)
    {
        UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Target->GetRootComponent());
        if (PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
        {
            FVector ForwardDirection = Target->GetActorForwardVector();
            FVector Impulse = ForwardDirection * 50.f;

            PrimitiveComponent->AddImpulse(Impulse, NAME_None, true);
        }
    }
}
