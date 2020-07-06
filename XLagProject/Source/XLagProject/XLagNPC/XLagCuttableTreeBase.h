// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XLagCuttableTreeBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagCuttableTreeBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AXLagCuttableTreeBase();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMesh* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Params")
	float Age;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual ConstructorHelpers::FObjectFinder<UStaticMesh>* GetAsset() 
	{ 
		return nullptr; 
	}
	virtual void Initialize();

public:		
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	bool CanTake();
	bool CanCut();
	void Cut(int force);
	void UpdateAge(float age);

private:
	int Sustainability = 100;
	int State = 0;

};

UCLASS()
class XLAGPROJECT_API AXTree_HillTree_Tall_02 : public AXLagCuttableTreeBase
{
	GENERATED_BODY()

public:
	AXTree_HillTree_Tall_02() : AXLagCuttableTreeBase()
	{
		Initialize();
	}

protected:
	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetAsset() override
	{
		UE_LOG(LogTemp, Log, TEXT("Call GetAsset from AXTree_HillTree_Tall_02"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/HillTree_Tall_02/HillTree_Tall_02"));
		return &Asset;
	}
};

UCLASS()
class XLAGPROJECT_API AXTree_ScotsPineTall_01 : public AXLagCuttableTreeBase
{
	GENERATED_BODY()
public:
	AXTree_ScotsPineTall_01() : AXLagCuttableTreeBase()
	{
		Initialize();
	}

protected:
	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetAsset() override
	{
		UE_LOG(LogTemp, Log, TEXT("Call GetAsset from AXTree_ScotsPineTall_01"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/ScotsPineTall_01/ScotsPineTall_01"));
		return &Asset;
	}
};

UCLASS()
class XLAGPROJECT_API AXTree_HillTree_02 : public AXLagCuttableTreeBase
{
	GENERATED_BODY()
public:
	AXTree_HillTree_02() : AXLagCuttableTreeBase()
	{
		Initialize();
	}

protected:
	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetAsset() override
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/HillTree_02/HillTree_02"));
		return &Asset;
	}
};