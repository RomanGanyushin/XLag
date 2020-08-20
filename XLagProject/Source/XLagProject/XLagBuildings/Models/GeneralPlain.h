#pragma once

#include "GeneralPlain.generated.h"

USTRUCT()
struct FUnboundedVector3
{
	GENERATED_BODY()

	UPROPERTY() FString X;
	UPROPERTY() FString Y;
	UPROPERTY() FString Z;
};

USTRUCT()
struct FUnboundedRotator3
{
	GENERATED_BODY()

	UPROPERTY() FString Pitch;
	UPROPERTY() FString Yaw;
	UPROPERTY() FString Roll;
};

USTRUCT()
struct FRepeat
{
	GENERATED_BODY()
	UPROPERTY() FString Count;
	UPROPERTY() FUnboundedVector3 IncrementalPosition;
	UPROPERTY() FUnboundedRotator3 IncrementalRotation;
};

USTRUCT()
struct FGeneralStep
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() FUnboundedVector3 Local;
	UPROPERTY() TArray<FString> SubStepIds;
};

USTRUCT()
struct FSubStep
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() FUnboundedVector3 Local;
	UPROPERTY() FUnboundedRotator3 Orientation;
	UPROPERTY() FString Action;
	UPROPERTY() FString ElementId;
	UPROPERTY() FRepeat Repeat;
};

USTRUCT()
struct FGeneralPlain
{
	GENERATED_BODY()

	UPROPERTY() FString BuildingName;
	UPROPERTY() TArray<FGeneralStep> GeneralSteps;
	UPROPERTY() TArray<FSubStep> SubSteps;
};
