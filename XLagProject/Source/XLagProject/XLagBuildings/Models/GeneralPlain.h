#pragma once

#include "GeneralPlain.generated.h"

USTRUCT() struct FXLagBuildParameter
{
	GENERATED_BODY()

	UPROPERTY() FString Name;
	UPROPERTY() FString Value;
	FString NameInExpression() const { return FString::Printf(TEXT("{%s}"), *Name); }
};


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

	const bool IsEmpty() const { return Local.IsEmpty() && Orientation.IsEmpty() && OffsetLocal.IsEmpty() && OffsetOrientation.IsEmpty(); }
};

USTRUCT()
struct FRepeat : public FPositionSetup
{
	GENERATED_BODY()
	UPROPERTY() FString Count;

	const bool IsEmpty() const { return Count.IsEmpty() && FPositionSetup::IsEmpty(); }
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
	UPROPERTY() TArray<FString> ElementParams;
	UPROPERTY() FRepeat Repeat;
};

USTRUCT()
struct FXProfilePoint
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() FString U;
	UPROPERTY() FString V;
};

USTRUCT()
struct FXElementProfile
{
	GENERATED_BODY()

	UPROPERTY() TArray<FXProfilePoint> Points;
	UPROPERTY() TArray<FString> Contur;
	UPROPERTY() TArray<FString> Mesh;
};

USTRUCT()
struct FXElementGeometry
{
	GENERATED_BODY()

	UPROPERTY() FXElementProfile Profile;
	UPROPERTY() FString Plane;
	UPROPERTY() FString Extrude;
};

USTRUCT()
struct FBuildingElement
{
	GENERATED_BODY()

	UPROPERTY() FString Id;
	UPROPERTY() FString Type;
	UPROPERTY() FString Length;
	UPROPERTY() FString Width;
	UPROPERTY() FString Height;
	UPROPERTY() FString Material;
	UPROPERTY() FXElementGeometry Geometry;
};

USTRUCT()
struct FGeneralPlain
{
	GENERATED_BODY()

	UPROPERTY() FString BuildingName;
	UPROPERTY() TArray<FGeneralStep> GeneralSteps;
	UPROPERTY() TArray<FSubStep> SubSteps;
	UPROPERTY() TArray<FXLagBuildParameter> Parameters;
	UPROPERTY() TArray<FBuildingElement> Elements;
};
