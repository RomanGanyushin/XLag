#pragma once
#include "XLagCropStage.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropStage
{
	GENERATED_BODY()

	// ����� ������ (� ���������).
	// �������� �� ���� ������� ������ ���� 100%.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PartOfTimeLife = 100;

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