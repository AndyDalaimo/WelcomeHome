// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "ArtifactData.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(28.0f, 74.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 10000.0f); // ...at this rotation rate

	// Movement Speed
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller
	
	// Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = true; // Camera does rotate relative to arm

	// Player Inventory
	PlayerInventory = CreateDefaultSubobject<UPlayerInventory>(TEXT("PlayerInventory"));
}


// Called when the game starts or when spawned   
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		//Interact 
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
		//Journal
		EnhancedInputComponent->BindAction(JournalAction, ETriggerEvent::Started, this, &APlayerCharacter::Journal);

	}
}



// Called when Player gives input to move PlayerCharacter
void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);	
		
		// Rotate Actor in Direction they are moving
		SetActorRotation(FRotator(0, this->GetDirection(MovementVector), 0));
	}
}

// Find direction player is walking in and return to Move()
float APlayerCharacter::GetDirection(FVector2D Movement)
{
	float direction = 0;

	if (Movement.Y <= -.5f) {
		direction += 180.f;

		if (Movement.X >= .5f) direction -= 45.f;

		else if (Movement.X <= -.5f) direction += 45.f;
	}
	else if (Movement.Y >= .5f) {
		if (Movement.X >= .5f) direction += 45.f;

		else if (Movement.X <= -.5f) direction -= 45.f;

	}
	else if (Movement.X >= .5f) direction += 90.f;

	else if (Movement.X <= -.5f) direction -= 90.f;

	return direction;
}



// Called when Player gives input to Interact with World Objects
void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Interact")));

	//  Line Trace to check for Artifact/Interactable Interface

	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 100.f;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	FString ArtifactString = "ArtifactData";
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, 
		ECollisionChannel::ECC_Visibility, Params, FCollisionResponseParams()) && HitResult.GetActor()->IsValidLowLevel())
	{
		// TEMP/TESTING: Find and list all components attached to actor. If ArtifactData, Retrieve Data and pull UI
		TSet<UActorComponent*> Comps = HitResult.GetActor()->GetComponents(); 

		for (UActorComponent* i : Comps)
		{
			UE_LOG(LogTemp, Log, TEXT("Components: %s"), *i->GetName());

			// Found the Artifact Data. Pass to Artifact interact interface
			if (*i->GetName() == ArtifactString)
			{
				UE_LOG(LogTemp, Log, TEXT("FOUND EM"));
				ArtifactInteract((AArtifact*)HitResult.GetActor());
				return;
			}
		}
	}

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5.0f, 0, 5.0f);

}


// Called if player interacts with Artifact. Will Call ArtifactInteractUI to update UI and Journal
void APlayerCharacter::ArtifactInteract(AArtifact* Artifact)
{
	UE_LOG(LogTemp, Warning, TEXT("Artifact Found: %s\n Artifact Name: %s\n Artifact Description: %s\n"), 
		*Artifact->GetName(), *Artifact->ItemName, *Artifact->Description);
	

	CurrentArtifactName = StaticCast<FString>(*Artifact->ItemName);
	CurrentArtifactDescription = StaticCast<FString>(*Artifact->Description);

	// Add Artifact into Player's Inventory. Can be checked in Journal Action
	PlayerInventory->AddArtifact(Artifact);

	// Destroy Artifact in world
	Artifact->Destroy();

	// Call ArtifactUIEvent() (Blueprint Function)  which will ShowWidget() in GameInstance class
	ArtifactUIEvent();
	
}



// Event triggered in BP_Player When player interacts with Artifact Object in World
void APlayerCharacter::ArtifactUIEvent_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ArtifactUI Setup Called"));
}

// Input JournalAction called by Player. 
// TODO: Created pages within UI that starts with Inventory and can switch to Journal
void APlayerCharacter::Journal(const FInputActionValue& Value)
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	OpenJournal();
}

// Event triggered in BP_Player When player checks inventory/journal 
void APlayerCharacter::OpenJournal_Implementation()
{
	// PlayerInventory->PrintInventory();
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


