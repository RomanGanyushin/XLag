#include "GeneralPlainSerialization.h"
#include "JsonObjectConverter.h"

TSharedPtr<FGeneralPlain> UGeneralPlainSerialization::LoadFromFile(FString filename)
{
	FGeneralPlain* result = new FGeneralPlain();

	FString AbsolutePathFile = FPaths::ProjectUserDir();
	FString Content;
	
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding Dir: %s"), *AbsolutePathFile);

	auto& platformFileManager = FPlatformFileManager().Get().GetPlatformFile();
	auto filepath = FPaths::Combine(AbsolutePathFile, filename);
	//auto file = platformFileManager.OpenRead(*filename);
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding Loading : %s"), *filepath);

	if (platformFileManager.FileExists(*filepath))
	{
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding file found"));
		FFileHelper::LoadFileToString(Content, *filepath);
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding - %s "), *Content);

	
		if (FJsonObjectConverter::JsonObjectStringToUStruct(Content, result, 0, 0))
		{
			UE_LOG(LogTemp, Log, TEXT("AXLagBuilding Convert success"));
			UE_LOG(LogTemp, Log, TEXT("AXLagBuilding ID= %s"), *result->BuildingName);
			UE_LOG(LogTemp, Log, TEXT("AXLagBuilding General Step Cuunt = %d"), result->GeneralSteps.Num());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("vAXLagBuilding Convert fail"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AXLagBuilding File not found : %s"), *filepath);
	}

	return MakeShareable(result);
}