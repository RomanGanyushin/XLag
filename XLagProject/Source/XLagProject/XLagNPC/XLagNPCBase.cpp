// Fill out your copyright notice in the Description page of Project Settings.

#include "XLagNPCBase.h"
#include "Math/Vector.h"
#include "../XLagTasks/XLagTaskManager.h"

// Sets default values
AXLagNPCBase::AXLagNPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Baggage = NewObject<UXLagNPCBaggage>();
}

// Called when the game starts or when spawned
void AXLagNPCBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Subscibes
	auto manager = AXLagTaskManager::GetTaskManager();
	if (manager != nullptr)
	{
		manager->PerformersSearchEvent.AddDynamic(this, &AXLagNPCBase::OnTaskManager_TaskChanged);
	}
}

// Called every frame
void AXLagNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AXLagNPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AXLagNPCBase::OnTaskManager_TaskChanged(AXLagTaskManager* manager, UXLagTaskBase* task)
{
	if (manager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("OnTaskManager_TaskChanged: argument 'manager' is null"));
	}

	if (task == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("OnTaskManager_TaskChanged: argument 'task' is null"));
	}

	if (task->ProfessionType != GetCurrentProfession()) // Если профессия не совпадает, то выходим из обработчика.
		return;

	if (CurrentTask != nullptr) // Проверяем что персонаж свободен.
	{
		return;
	}


	if (!CanConfirmTask(task)) // Проверяем, что персонаж может выполнить задачу. 
		return;

	// Подаем заявку на выполнение задач.
	manager->ApplyForTask(this, task);
}

void AXLagNPCBase::OfferAccept(UXLagTaskBase* task)
{
	CurrentTask = task;
}

void AXLagNPCBase::FreeOf(UXLagTaskBase* task)
{
	CurrentTask = nullptr;
}


