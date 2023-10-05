// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Artifact.h"
#include "PlayerInventory.generated.h"


USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

public:

	FItem()
		: Name("")
		, Description("")
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact Info")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact Info")
	FString Description;


};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WELCOMEHOME_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	TArray<FItem> PlayerArtifacts;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Push Artifact Collected in world into player Inventory
	void AddArtifact(AArtifact* artifact);

	// Print Inventory -- TODO: Soon to be implemented to Journal/Inventory managment 
	void PrintInventory();

		
};
