// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


// Set up UI Widgets and give references for GameInsatance
// TODO -- Set up Journal UI. Blueprint Functions made in Player and currently prints out all of Inventory
UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ArtifactUIWidget(TEXT("/Game/UI/WBP_ArtifactUI"));
	// Check if reference is Valid
	if (!ensure (ArtifactUIWidget.Class != nullptr)) return;

	ArtifactUIWidgetClass = ArtifactUIWidget.Class;

}

// Check if reference to Widget Class is valid
void UMyGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Widget Class Found: %s"), *ArtifactUIWidgetClass->GetName());
}

// Display Artifact Widget when Player Interacts with object in world
void UMyGameInstance::ShowArtifactUIWidget()
{
	// Create Widget and add it to the viewport
	UUserWidget* ArtifactUI = CreateWidget<UUserWidget>(this, ArtifactUIWidgetClass);
	ArtifactUI->AddToViewport();

	// Get reference to Player Controller
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	// Set up input parameters
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(ArtifactUI->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// Set Input Mode
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
	

}


// Called when Player clicks on Exit Button in viewport. 
// Give control back to player and remove mouse cursor from screen
void UMyGameInstance::ExitArtifactWidget()
{
	// Get reference to Player Controller
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	// Set up input parameters
	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);

	// Set Input Mode
	PlayerController->EnableInput(PlayerController);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}
