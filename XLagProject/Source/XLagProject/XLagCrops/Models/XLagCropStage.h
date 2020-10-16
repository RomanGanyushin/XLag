#pragma once
#include "XLagCropStage.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropStage
{
	GENERATED_BODY()

	// ����� ������ (� ������� �����).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StageLifeTime = 1;

	// ������� � ������ ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartScale = 0.1f;

	// ������� � ����� ������.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FinalScale = 1.0f;
	
	// ������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	UStaticMesh* CropTemplate;
};