// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Artifact.generated.h"


UCLASS()
class WELCOMEHOME_API AArtifact : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AArtifact();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = ArtifactDescription, meta = (AllowPrivateAccess = "true"))
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = ArtifactDescription, meta = (AllowPrivateAccess = "true"))
	FString Description;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
