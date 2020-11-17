// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Common/ProfessionTypeEnum.h"
#include "XLagNPCBaggage.h"
#include "XLagNPCBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagNPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXLagNPCBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Текущая задача, выполняемая песонажем.
	UPROPERTY()  UXLagTaskBase* CurrentTask;

	// Утвердить предложение по работе.
	UFUNCTION() virtual void OfferAccept(UXLagTaskBase* task);

	// Освободить от работы.
	UFUNCTION() virtual void FreeOf(UXLagTaskBase* task);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UXLagNPCBaggage *Baggage;

protected:

	// 
	UFUNCTION() virtual void OnTaskManager_TaskChanged(AXLagTaskManager* manager, UXLagTaskBase* task);
	
protected:
	virtual ProfessionTypeEnum GetCurrentProfession() { return ProfessionTypeEnum::Unknow; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) {return false; }
};
