// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "XLagDynamicTerrainBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagDynamicTerrainBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagDynamicTerrainBase();

	// Terrain scene property
	UPROPERTY(VisibleAnywhere)
	USceneComponent* TerrainScene;

	// Terrain layers array
	UPROPERTY(VisibleAnywhere)
	TArray<UProceduralMeshComponent*> TerrainLayers;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
