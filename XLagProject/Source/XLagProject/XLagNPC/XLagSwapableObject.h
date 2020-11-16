#pragma once
#include "../XLagDynamicObject/XLagDynamicObject.h"
#include "XLagSwapableObject.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagSwapableObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagSwapableObject();

	UFUNCTION()
	virtual void AssignObject(const FXLagDynamicObject& object);

	UPROPERTY()
	int32 ObjectId;
};