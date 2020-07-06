// Fill out your copyright notice in the Description page of Project Settings.

#include "XLagNPCBase.h"
#include "Math/Vector.h"

// Sets default values
AXLagNPCBase::AXLagNPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXLagNPCBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AXLagNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (IsExistTask())
	{
		NpcTask->Execute(this, DeltaTime);
	}
}

// Called to bind functionality to input
void AXLagNPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


