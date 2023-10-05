// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Artifact.h"
#include "PlayerInventory.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class WELCOMEHOME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	// Camera boom positioning the camera behind the character 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Follow Camera on Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Mapping Context 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// Move Input Action 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Interact input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	// Journal input Acion
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JournalAction;

	// Player Inventory
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UPlayerInventory* PlayerInventory;
	
	// Temp Artifact details when Player interacts. Used in Artifact Widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Artifact, meta = (AllowPrivateAccess = "true"))
	FString CurrentArtifactName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Artifact, meta = (AllowPrivateAccess = "true"))
	FString CurrentArtifactDescription;



public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement Input
	void Move(const FInputActionValue& Value);

	// Interact Input
	void Interact(const FInputActionValue& Value);

	// Journal Input
	void Journal(const FInputActionValue& Value);

	// Determine direction Player is walking 
	float GetDirection(FVector2D Movement);

	// Pass Artifact actor to UIUpdate and Pull Artifact Reference
	void ArtifactInteract(AArtifact* Artifact); 

	



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintNativeEvent)
	void ArtifactUIEvent();

	UFUNCTION(BlueprintNativeEvent)
	void OpenJournal();
};
