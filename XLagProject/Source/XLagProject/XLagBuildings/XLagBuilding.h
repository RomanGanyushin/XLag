// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Processings/XLagBuildProcessing.h"
#include "XLagBuilding.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXLagBuilding();

	/// Selection scene property
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintSetter = DoShowPreview)
		bool ShowPreview = false;

	UFUNCTION(BlueprintSetter)
		void DoShowPreview(bool isShow);

	UFUNCTION()
		void Build();

	UPROPERTY(VisibleAnywhere)
		bool IsBuildComplited;

	void SetGeneralPlain(const FGeneralPlain& plain);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FGeneralPlain _plain;
	UPROPERTY() UXLagBuildProcessing *_processing = nullptr;
};
