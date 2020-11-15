// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/StaticMeshActor.h"
#include "../XLagDynamicObject/XLagDynamicObject.h"
#include "XLagCuttableTreeBase.generated.h"

enum AXLagCuttableTreeState
{
	Growing,
	Falling,
	Fallen,
	Timber
};


UCLASS()
class XLAGPROJECT_API AXLagCuttableTreeBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AXLagCuttableTreeBase();

	void SetObject(FXLagDynamicObject* object);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMesh* Mesh;

	// Возраст
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Params")
	float Age;

	UPROPERTY(BlueprintReadOnly, Category = "Current State Properties")
	float TimberDiameter = 0.4;

	UPROPERTY(BlueprintReadOnly, Category = "Current State Properties")
	float TimberLength = 4;

	// Состояние дерева.
	AXLagCuttableTreeState State = AXLagCuttableTreeState::Growing;
	
	//long PlaceId;

	ConstructorHelpers::FObjectFinder<UStaticMesh>*fv;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual ConstructorHelpers::FObjectFinder<UStaticMesh>* GetAsset() 
	{ 
		return nullptr; 
	}

	virtual ConstructorHelpers::FObjectFinder<UStaticMesh>* GetTimberAsset()
	{
		return nullptr;
	}

	virtual void Initialize();

public:		
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Рубить.
	void Cut(int force);
	
	// Проверяет, что дерево срублено.
	bool IsCutted();

	// Проверяет, что дерево можно обтесывать.
	bool CanBroach();

	// Обтесать дерево до бревна.
	void Broach(int force);

	// Проверяет что дерево обтесано до бревна.
	bool IsTimber();

	// Обновить возраст до указанного.
	void UpdateAge(float age);



protected:
	int Sustainability = 1000;

	UStaticMeshComponent *AliveTree;
	UStaticMesh *TimberObject;

	FXLagDynamicObject* _object = nullptr;

	UFUNCTION()
	void OnPropertyChanged(uint8 id);
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

	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetTimberAsset() override
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/HillTree_02/HillTree_02_Timber"));
		return &Asset;
	}
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

	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetTimberAsset() override
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/HillTree_Tall_02/HillTree_Tall_01_Timber"));
		return &Asset;
	}
};

UCLASS()
class XLAGPROJECT_API AXTree_ScotsPine_01 : public AXLagCuttableTreeBase
{
	GENERATED_BODY()
public:
	AXTree_ScotsPine_01() : AXLagCuttableTreeBase()
	{
		Initialize();
	}

protected:
	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetAsset() override
	{
		UE_LOG(LogTemp, Log, TEXT("Call GetAsset from AXTree_ScotsPine_01"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/ScotsPineTall_01/ScotsPineTall_01"));
		return &Asset;
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetTimberAsset() override
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/ScotsPineTall_01/ScotsPineTall_01_Timber"));
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

	ConstructorHelpers::FObjectFinder<UStaticMesh>* GetTimberAsset() override
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Game/KiteDemo/Environments/Trees/ScotsPineTall_01/ScotsPineTall_01_Timber"));
		return &Asset;
	}
};

