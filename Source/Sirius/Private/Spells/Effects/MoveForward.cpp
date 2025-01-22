// Fill out your copyright notice in the Description page of Project Settings.


#include "Spells/Effects/MoveForward.h"

// Sets default values
AMoveForward::AMoveForward()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    bShouldBeTriggeredOnceTimeOnly = true;

}

// Called when the game starts or when spawned
void AMoveForward::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMoveForward::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMoveForward::ApplyEffect(AActor* Target)
{
    if (Target)
    {
        UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(Target->GetRootComponent());
        if (PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
        {
            FVector ForwardDirection = Target->GetActorForwardVector();
            FVector Impulse = ForwardDirection * 6000.f;

            PrimitiveComponent->AddImpulse(Impulse, NAME_None, true);
        }
    }
}
