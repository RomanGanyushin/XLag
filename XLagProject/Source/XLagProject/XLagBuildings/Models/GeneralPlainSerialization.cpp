#include "GeneralPlainSerialization.h"
#include "JsonObjectConverter.h"

FGeneralPlain* UGeneralPlainSerialization::LoadFromFile(FString filename)
{
	FGeneralPlain* result = nullptr;
	FString Content;

	auto& platformFileManager = FPlatformFileManager().Get().GetPlatformFile();
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding Loading : %s"), *filename);

	if (platformFileManager.FileExists(*filename))
	{
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding file found"));
		FFileHelper::LoadFileToString(Content, *filename);
		UE_LOG(LogTemp, Log, TEXT("AXLagBuilding - %s "), *Content);

		result = new FGeneralPlain();
		if (FJsonObjectConverter::JsonObjectStringToUStruct(Content, result, 0, 0))
		{
			UE_LOG(LogTemp, Log, TEXT("AXLagBuilding Convert success"));
			UE_LOG(LogTemp, Log, TEXT("AXLagBuilding ID= %s"), *result->BuildingName);
			UE_LOG(LogTemp, Log, TEXT("AXLagBuilding General Step Cuunt = %d"), result->GeneralSteps.Num());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("vAXLagBuilding Convert fail"));
			delete result;
			result = nullptr;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AXLagBuilding File not found : %s"), *filename);
	}

	return result;
}

TArray<FString> UGeneralPlainSerialization::ScanFiles()
{
	TArray<FString> result;
	FString absolutePathFile = FPaths::EngineUserDir();
	UE_LOG(LogTemp, Log, TEXT("AXLagBuilding Dir: %s"), *absolutePathFile);

	auto& platformFileManager = FPlatformFileManager().Get().GetPlatformFile();
	platformFileManager.FindFiles(result, *absolutePathFile, *FString(TEXT(".json")));
	return result;
}