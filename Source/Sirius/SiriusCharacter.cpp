// Copyright Epic Games, Inc. All Rights Reserved.

#include "SiriusCharacter.h"
#include "SiriusProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Spells/Effects/DefaultEffect.h" 
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASiriusCharacter

ASiriusCharacter::ASiriusCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ASiriusCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void ASiriusCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BlendMaterial)
	{
		/*
		BlendMaterial->
		*/
	}

	if (GrabbedObject)
	{
		// Calculer la position cible pour l'objet saisi
		FVector GrabLocation = FirstPersonCameraComponent->GetComponentLocation() +
			FirstPersonCameraComponent->GetForwardVector() * GrabDistance;

		GrabbedObject->SetWorldLocation(GrabLocation);
	}
}

//////////////////////////////////////////////////////////////////////////// Input

void ASiriusCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Started, this, &ASiriusCharacter::GrabOrDrop);

		EnhancedInputComponent->BindAction(PickupStaffAction, ETriggerEvent::Started, this, &ASiriusCharacter::PickupStaff);
		EnhancedInputComponent->BindAction(UseStaffAction, ETriggerEvent::Started, this, &ASiriusCharacter::UseStaff);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASiriusCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASiriusCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASiriusCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASiriusCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASiriusCharacter::GrabOrDrop()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab"));

	if (GrabbedObject)
	{
		// Si un objet est saisi, le relâcher
		GrabbedObject->SetSimulatePhysics(true);
		GrabbedObject->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics); // Réactiver les collisions
		GrabbedObject = nullptr;
		return;
	}

	// Sinon, essayer d'attraper un objet
	TraceForObject();
}

void ASiriusCharacter::TraceForObject()
{
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + FirstPersonCameraComponent->GetForwardVector() * TraceDistance;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	// Lancer un trace pour détecter un objet
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		// Vérifier si l'objet est physique
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		if (HitComponent && HitComponent->IsSimulatingPhysics())
		{
			UE_LOG(LogTemp, Warning, TEXT("ATTRAP !"));

			GrabbedObject = HitComponent;

			// Désactiver la physique pour le maintenir
			GrabbedObject->SetSimulatePhysics(false);
			GrabbedObject->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

void ASiriusCharacter::PickupStaff()
{
	if (EquippedStaff)
	{
		DropStaff();
		return;
	}

	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVector = FirstPersonCameraComponent->GetForwardVector();
	FVector End = Start + (ForwardVector * 500.0f); // Rayon de 500 unités

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore le joueur dans le raycast

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params))
	{
		// Vérifier si l'objet touché est un AStaff
		AStaff* DetectedStaff = Cast<AStaff>(HitResult.GetActor());
		if (DetectedStaff)
		{
			// Équiper le bâton
			EquippedStaff = DetectedStaff;

			AttachToComponent(GetMesh1P(), FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("GripPoint")));

			EquippedStaff->SetActorEnableCollision(false);
			EquippedStaff->StaffMesh->SetSimulatePhysics(false);

			if (Mesh1P->DoesSocketExist(TEXT("GripPoint")))
			{
				EquippedStaff->SetActorLocation(Mesh1P->GetSocketLocation(TEXT("GripPoint")));
				UE_LOG(LogTemp, Warning, TEXT("Equiped"));
			}
		}
	}
}

void ASiriusCharacter::DropStaff()
{
	if (EquippedStaff)
	{
		EquippedStaff->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		EquippedStaff->SetActorEnableCollision(true);
		EquippedStaff->StaffMesh->SetSimulatePhysics(true);

		FVector DropLocation = GetActorLocation() + (FirstPersonCameraComponent->GetForwardVector() * 100.0f);
		DropLocation.Z += 50.0f;
		EquippedStaff->SetActorLocation(DropLocation);

		FRotator ResetRotation = FRotator(0.0f, 0.0f, 0.0f);
		EquippedStaff->SetActorRotation(ResetRotation);

		EquippedStaff = nullptr;
	}
}

void ASiriusCharacter::UseStaff()
{
	if (EquippedStaff)
	{
		EquippedStaff->LogResults();

		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			FVector CameraLocation;
			FRotator CameraRotation;

			PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

			FVector SpawnLocation = CameraLocation + CameraRotation.Vector() * 120.0f;
			FRotator SpawnRotation = CameraRotation;

			ASpell* SpawnedSpell = GetWorld()->SpawnActor<ASpell>(ASpell::StaticClass(), SpawnLocation, SpawnRotation);

			if (SpawnedSpell)
			{
				SpawnedSpell->Forme = EquippedStaff->ResultForme;
				SpawnedSpell->Element = EquippedStaff->ResultElement;
				SpawnedSpell->Effet = EquippedStaff->ResultEffet;

				SpawnedSpell->ApplySpell();

				for (int32 i = 0; i < EquippedStaff->FormesListe.Num(); ++i)
				{
					SpawnedSpell->FormesListe.Add(EquippedStaff->FormesListe[i]);
					SpawnedSpell->ElementsListe.Add(EquippedStaff->ElementsListe[i]);
					SpawnedSpell->EffetsListe.Add(EquippedStaff->EffetsListe[i]);
				}
			}
		}
	}
}
