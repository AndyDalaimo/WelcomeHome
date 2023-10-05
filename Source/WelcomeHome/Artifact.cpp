// Fill out your copyright notice in the Description page of Project Settings.


#include "Artifact.h"

// Sets default values
AArtifact::AArtifact() : ItemName("NAME"), Description("DESCRIPTION")
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AArtifact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArtifact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
