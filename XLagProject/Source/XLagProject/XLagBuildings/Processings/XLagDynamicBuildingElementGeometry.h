#pragma once

#include "../Models/GeneralPlain.h"
#include "../../Abstracts/GeometryBuilderAbstract.h"
#include "XLagBuildParameterEvaluator.h"

class XLagDynamicBuildingElementGeometry : public GeometryBuilderAbstract
{
public:
	void Create(const FXElementGeometry& geometry, FXLagBuildParameterEvaluator* evaluator);

private:
	bool ExtractMesh(const FXElementProfile& profile, FXLagBuildParameterEvaluator* evaluator, TArray<FVector>& outResult);
	bool ExtractContur(const FXElementProfile& profile, FXLagBuildParameterEvaluator* evaluator, TArray<FVector>& outResult);
};