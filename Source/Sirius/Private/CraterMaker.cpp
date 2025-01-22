// Fill out your copyright notice in the Description page of Project Settings.


#include "CraterMaker.h"

ACraterMaker* ACraterMaker::SelfSelfCrater = nullptr;

// Sets default values
ACraterMaker::ACraterMaker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACraterMaker::BeginPlay()
{
	Super::BeginPlay();

    SelfSelfCrater = this;
	landscape = Cast<ALandscape>(UGameplayStatics::GetActorOfClass(GetWorld(), ALandscape::StaticClass()));
	
	// AdjustLandscapeAtWorldLocation({9280,0,-1768}, 3000, 1);
}

// Called every frame
void ACraterMaker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    APlayerController* currentPlayerController = GetWorld()->GetFirstPlayerController();
    
    if (currentPlayerController->WasInputKeyJustPressed(EKeys::P))
	{
		OnPKeyPressed();
	}
}



void ACraterMaker::AdjustLandscapeAtWorldLocation(const FVector& WorldLocationBase, float AdjustRadius, float EdgeBlendFactor, float Depth)
{
    FVector WorldLocation = WorldLocationBase + FVector(0, 0, Depth);
	if (!landscape) return;
    EdgeBlendFactor = FMath::Clamp(EdgeBlendFactor, 0.0f, 1.0f);

    if (!landscape->bCanHaveLayersContent)
    {
    	landscape->ToggleCanHaveLayersContent();
	}

    ULandscapeInfo* LandscapeInfo = landscape->GetLandscapeInfo();
    
    if (!LandscapeInfo) return;

    FIntRect LandscapeExtent;
    if (!LandscapeInfo->GetLandscapeExtent(LandscapeExtent)) return;

    const FVector LandscapeOrigin = landscape->GetActorLocation();
    const FVector LandscapeScale = landscape->GetActorScale3D();

    // Convert world location to landscape-space coordinates
    FVector LocalLocation = (WorldLocation - LandscapeOrigin) / LandscapeScale;
    int32 CenterX = FMath::RoundToInt(LocalLocation.X);
    int32 CenterY = FMath::RoundToInt(LocalLocation.Y);
    int32 AdjustRadiusInGridUnits = FMath::CeilToInt(AdjustRadius / LandscapeScale.X);

    // Calculate the bounds of the affected area
    int32 MinX = FMath::Clamp(CenterX - AdjustRadiusInGridUnits, LandscapeExtent.Min.X, LandscapeExtent.Max.X);
    int32 MinY = FMath::Clamp(CenterY - AdjustRadiusInGridUnits, LandscapeExtent.Min.Y, LandscapeExtent.Max.Y);
    int32 MaxX = FMath::Clamp(CenterX + AdjustRadiusInGridUnits, LandscapeExtent.Min.X, LandscapeExtent.Max.X);
    int32 MaxY = FMath::Clamp(CenterY + AdjustRadiusInGridUnits, LandscapeExtent.Min.Y, LandscapeExtent.Max.Y);

    int32 Width = MaxX - MinX + 1;
    int32 Height = MaxY - MinY + 1;

    //Create an instance of FLandscapeEditDataInterface
    FHeightmapAccessor<false> HeightmapAccessor(LandscapeInfo);

    TArray<uint16> HeightData;
    HeightData.SetNum(Width * Height);

    // Get the current heightmap data
    HeightmapAccessor.GetDataFast(MinX, MinY, MaxX, MaxY, HeightData.GetData());

    // Calculate the target height based on WorldLocation.Z
    if (WorldLocation.Z > (LandscapeOrigin.Z + 4.f)) return;
    float BaseHeightInWorld = WorldLocation.Z - LandscapeOrigin.Z;
    const uint16 FlatHeightValue = 32768;
    uint16 TargetHeight = FMath::Clamp<uint16>(FlatHeightValue + BaseHeightInWorld * 128.0f / LandscapeScale.Z, 0, UINT16_MAX);

    for (int32 Y = 0; Y < Height; ++Y)
    {
        for (int32 X = 0; X < Width; ++X)
        {
            // Adjust the heightmap with a smooth falloff
            float Distance = FVector2D::Distance(FVector2D(X + MinX, Y + MinY), FVector2D(CenterX, CenterY));
            if (Distance > AdjustRadiusInGridUnits) continue;

            float EffectiveRadius = AdjustRadiusInGridUnits * EdgeBlendFactor;
            float NormalizedDistance = FMath::Clamp((Distance - (AdjustRadiusInGridUnits - EffectiveRadius)) / EffectiveRadius, 0.0f, 1.0f);
            float Falloff = (EdgeBlendFactor > 0.0f) ? FMath::SmoothStep(0.0f, 1.0f, 1.0f - NormalizedDistance) : 1.0f;

            uint16 CurrentHeight = HeightData[X + Y * Width];
            HeightData[X + Y * Width] = FMath::Lerp(CurrentHeight, TargetHeight, Falloff);
        }
    }

    // Set the new heightmap data
    HeightmapAccessor.SetData(MinX, MinY, MaxX, MaxY, HeightData.GetData());

    // Flush any changes to the heightmap
    HeightmapAccessor.Flush();
    // landscape->CreateLandscapeInfo();
    landscape->RecreateCollisionComponents();
    landscape->MarkComponentsRenderStateDirty();
    landscape->MarkPackageDirty(); 
    LandscapeInfo->UpdateAllAddCollisions(); 
}

void ACraterMaker::OnPKeyPressed()
{
    AdjustLandscapeAtWorldLocation(GetWorld()->GetFirstPlayerController()->GetTargetLocation(), adjustRadius, edgeBlendFactor, 100.f);
}