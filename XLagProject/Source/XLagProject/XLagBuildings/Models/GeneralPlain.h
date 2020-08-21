#pragma once

#include "GeneralPlain.generated.h"

USTRUCT()
struct FUnboundedVector3
{
	GENERATED_BODY()

	UPROPERTY() FString X;
	UPROPERTY() FString Y;
	UPROPERTY() FString Z;

	const bool IsEmpty() const { return X.IsEmpty() && Y.IsEmpty() && Z.IsEmpty(); }
};

USTRUCT()
struct FUnboundedRotator3
{
	GENERATED_BODY()

	UPROPERTY() FString Pitch;
	UPROPERTY() FString Yaw;
	UPROPERTY() FString Roll;

	const bool IsEmpty() const { return Pitch.IsEmpty() && Yaw.IsEmpty() && Roll.IsEmpty(); }
};

USTRUCT()
struct FPositionSetup
{
	GENERATED_BODY()

	UPROPERTY() FUnboundedVector3 Local;
	UPROPERTY() FUnboundedRotator3 Orientation;
	UPROPERTY() FUnboundedVector3 OffsetLocal;
	UPROPERTY() FUnboundedRotator3 OffsetOrientation;
};

USTRUCT()
struct FRepeat : public FPositionSetup
{
	GENERATED_BODY()
	UPROPERTY() FString Count;

	const bool IsEmpty() const { return Count.IsEmpty() && IsEmpty(); }
};


USTRUCT()
struct FGeneralStep : public FPositionSetup
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() TArray<FString> SubStepIds;
	UPROPERTY() FRepeat Repeat;
};

USTRUCT()
struct FSubStep : public FPositionSetup
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
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
