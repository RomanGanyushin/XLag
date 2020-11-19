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
	void BeginPlay() override;
protected:

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// ������������� �� ���������.
	UFUNCTION() virtual void DefaultInitialize();

	// ������� ������, ����������� ���������.
	UPROPERTY()  UXLagTaskBase* CurrentTask;

	// ��������� ����������� �� ������.
	UFUNCTION() virtual void OfferAccept(UXLagTaskBase* task);

	// ���������� �� ������.
	UFUNCTION() virtual void FreeOf(UXLagTaskBase* task);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UXLagNPCBaggage *Baggage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "NPC Searching")
	int32  FindCellIndex = -1;

protected:

	// 
	UFUNCTION() virtual void OnTaskManager_TaskChanged(AXLagTaskManager* manager, UXLagTaskBase* task);
	
protected:
	virtual ProfessionTypeEnum GetCurrentProfession() { return ProfessionTypeEnum::Unknow; }
	virtual bool CanConfirmTask(UXLagTaskBase* task) {return false; }
};
