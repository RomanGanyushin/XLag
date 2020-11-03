#pragma once

#include <map>
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "XLagNPCBase.h"
#include "XLagLooseStackBase.generated.h"

UCLASS()
class XLAGPROJECT_API AXLagLooseStackBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AXLagLooseStackBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void AddQuantity(float quantity);

	// �������� ���������� ���������� ��������.
	virtual float GetAvaibleQuantity();

	// ����������� �� ����������.
	virtual void Reserve(AXLagNPCBase *reserver, float quantity);

	// �������� ������� �� ����.
	virtual float TakeQuantity(AXLagNPCBase *npc, float quantity);

	// ���������, ��������������� �� �� ����������.
	virtual bool IsReservedFor(const AXLagNPCBase *npc) const;

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeX;

	UPROPERTY(VisibleAnywhere, Category = "Stack Properties")
		int SizeY;

	// ���������� ���������
	UPROPERTY(VisibleAnywhere, Category = "Current State Properties")
		float StackQuantity = 0;

	UPROPERTY(VisibleAnywhere)
		UProceduralMeshComponent* ThisStack;

private:
	void CreateView();
	std::map<const AXLagNPCBase *, float > _reserves;
};
