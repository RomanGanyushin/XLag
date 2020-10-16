#pragma once
#include "XLagCropStage.generated.h"

USTRUCT(BlueprintType)
struct FXLagCropStage
{
	GENERATED_BODY()

	// Время стадии (в игровых часах).
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StageLifeTime = 1;

	// Масштаб в начале стадии.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StartScale = 0.1f;

	// Масштаб в конце стадии.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FinalScale = 1.0f;
	
	// Шаблоны растения
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	UStaticMesh* CropTemplate;
};