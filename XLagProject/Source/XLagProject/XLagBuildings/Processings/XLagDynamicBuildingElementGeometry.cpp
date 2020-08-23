#include "XLagDynamicBuildingElementGeometry.h"

void XLagDynamicBuildingElementGeometry::Create(const FXElementGeometry& geometry, FXLagBuildParameterEvaluator* evaluator)
{
	Reset();

	int32 triIndex = 0;

	FVector extractVector = FVector(1, 0, 0) * evaluator->EvaluateFloat(geometry.Extrude);

	TArray<FVector> mesh;
	ExtractMesh(geometry.Profile, evaluator, mesh);

	for (int i = 0; i < mesh.Num(); i += 3)
	{
		AddTriangleMesh(mesh[i], mesh[i + 2], mesh[i + 1], triIndex);
	}

	for (int i = 0; i < mesh.Num(); i += 3)
	{
		AddTriangleMesh(mesh[i] + extractVector, mesh[i + 1] + extractVector, mesh[i + 2]+ extractVector, triIndex);
	}

	TArray<FVector> contur;
	ExtractContur(geometry.Profile, evaluator, contur);
	

	for (int i = 0; i < contur.Num(); i++)
	{
		AddQuadMesh(contur[i], contur[(i + 1) % contur.Num()], contur[(i + 1) % contur.Num()] + extractVector, contur[i] + extractVector, triIndex);
	}

}

bool XLagDynamicBuildingElementGeometry::ExtractMesh(const FXElementProfile& profile, FXLagBuildParameterEvaluator* evaluator, TArray<FVector>& outResult)
{
	TMap<int, FVector> pointTable;
	for (auto &it : profile.Points)
	{
		auto id = evaluator->EvaluateInt(it.Id);
		auto u = evaluator->Evaluate(it.U);
		auto v = evaluator->Evaluate(it.V);

		pointTable.Add(id, FVector(0, u, v));
	}

	for (auto& it: profile.Mesh)
	{
		auto pId = evaluator->EvaluateInt(it);
		outResult.Add(pointTable[pId]);
	}

	return true;
}


bool XLagDynamicBuildingElementGeometry::ExtractContur(const FXElementProfile& profile, FXLagBuildParameterEvaluator* evaluator, TArray<FVector>& outResult)
{
	TMap<int, FVector> pointTable;
	for (auto &it : profile.Points)
	{
		auto id = evaluator->EvaluateInt(it.Id);
		auto u = evaluator->Evaluate(it.U);
		auto v = evaluator->Evaluate(it.V);

		pointTable.Add(id, FVector(0, u, v));
	}

	for (auto& it : profile.Contur)
	{
		auto pId = evaluator->EvaluateInt(it);
		outResult.Add(pointTable[pId]);
	}

	return true;
}