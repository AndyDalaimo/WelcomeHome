// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WELCOMEHOME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	// Check if reference to Widget class is Valid
	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void ShowArtifactUIWidget();

	UFUNCTION(BlueprintCallable)
	void ExitArtifactWidget();

private:
	TSubclassOf<class UUserWidget> ArtifactUIWidgetClass;
};
