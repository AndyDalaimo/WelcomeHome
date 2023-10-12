// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "ArtifactData.generated.h"

// Struct Artifact Info - Will have name of Item and the Description to be placed
// in Artifact UI
USTRUCT(BlueprintType)
struct FArtifactInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FArtifactInfo()
		: Name("")
		, ItemTexture()
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact Info")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact Info")
	UTexture2D* ItemTexture;

	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WELCOMEHOME_API UArtifactData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArtifactData();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ItemDescription, meta = (AllowPrivateAccess = "true"))
	class UDataTable* ItemDescription;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
