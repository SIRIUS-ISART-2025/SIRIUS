#include "Staff.h"

AStaff::AStaff()
{
	PrimaryActorTick.bCanEverTick = true;

    StaffMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaffMesh"));
    RootComponent = StaffMesh;

    StaffMesh->SetCollisionProfileName(TEXT("PhysicsActor"));
    StaffMesh->SetSimulatePhysics(true);
}

void AStaff::BeginPlay()
{
	Super::BeginPlay();
}

void AStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStaff::SetResults(EElement ElementName, EForme FormeName, EEffet EffetName, AAElement* ResultElement_, AAForme* ResultForme_, AAEffet* ResultEffet_)
{
    ResultElementName = ElementName;
    ResultFormeName = FormeName;
    ResultEffetName = EffetName;

    ResultElement = ResultElement_;
    ResultForme = ResultForme_;
    ResultEffet = ResultEffet_;
}

void AStaff::LogResults()
{
    UE_LOG(LogTemp, Warning, TEXT("Element: %s, Forme: %s, Effet: %s"),
        *UEnum::GetValueAsString(ResultElementName),
        *UEnum::GetValueAsString(ResultFormeName),
        *UEnum::GetValueAsString(ResultEffetName));
} 