// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Add artifact into Player Inventory
// TODO -- Do I want this as a struct, or a Reference of the actual artifact
void UPlayerInventory::AddArtifact(AArtifact* artifact)
{
	UE_LOG(LogTemp, Warning, TEXT("Add Artifact Called"));

	FItem item;
	item.Name = *artifact->ItemName;
	item.Description = *artifact->Description;
	
	PlayerArtifacts.Add(item);

}

// Print Items in inventory. Will be Implemented in Journal to display which items the Player has in Possession
void UPlayerInventory::PrintInventory()
{
	for (auto i : PlayerArtifacts)
	{
		UE_LOG(LogTemp, Warning, TEXT("Item in Inventory: %s %s"), *i.Name, *i.Description);
	}
}




// Called every frame
/*void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

