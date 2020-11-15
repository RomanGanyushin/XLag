#pragma once
#include "XLagObjectProperties.generated.h"

struct FXLagObjectProperties;

USTRUCT(BlueprintType)
struct FXLagObjectPropertyPackage
{
	GENERATED_BODY();

	FXLagObjectPropertyPackage() {}
	FXLagObjectPropertyPackage(const FVariant& value);
	void Pack(const FVariant& value);
	const FVariant UnPack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TArray<uint8> Data;

	const bool operator==(const FVariant& value);

	template <typename T>
	const FVariant UnPack() const
	{
		T Result;
		FMemoryReader Reader(Data, true);
		Reader << Result;
		return Result;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPropertyChangedDelegate, uint8, id);

USTRUCT(BlueprintType)
struct FXLagObjectProperties
{
	GENERATED_BODY();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TMap<uint8, FXLagObjectPropertyPackage> Properties;

	// —обытие возникающее при изменение свойства.
	UPROPERTY(BlueprintAssignable)
		FPropertyChangedDelegate PropertyChangedEvent;

	bool HasValue(uint8 id) const;
	void SetValue(uint8 id, const FVariant& value);

	template <typename T> T GetValue(const uint8 id) const 
	{
		if (!HasValue(id))
		{
			return T();
		}
		else
		{
			return Properties[id].UnPack<T>().GetValue<T>();
		}
	}

	void SetProperties(const FXLagObjectProperties& source);
};

