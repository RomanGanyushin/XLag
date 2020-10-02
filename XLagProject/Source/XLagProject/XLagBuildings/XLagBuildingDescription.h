#pragma once
#include "Models/GeneralPlain.h"
#include "XLagBuildingDescription.generated.h"

USTRUCT(BlueprintType) struct  FXLagBuildingDescription
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
		bool IsExist = false;

	UPROPERTY(BlueprintReadOnly)
		int PositionX;

	UPROPERTY(BlueprintReadOnly)
		int PositionY;

	void SetGeneralPlain(FGeneralPlain& generalPlain);
	const FGeneralPlain& GetGeneralPlain() const;


	UPROPERTY() FGeneralPlain _generalPlain;
};