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

USTRUCT(BlueprintType)
struct FXLagObjectProperties
{
	GENERATED_BODY();
	virtual ~FXLagObjectProperties() = default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame)
	TMap<uint8, FXLagObjectPropertyPackage> Properties;

	bool HasValue(uint8 id) const;
	virtual void SetValue(uint8 id, const FVariant& value);

	template <typename T> T GetValue(const uint8 id) const 
	{
		if (!HasValue(id))
		{
			return T();
		}
		else
		{
			T Result;
			FMemoryReader Reader(Properties[id].Data, true);
			Reader << Result;
			return Result;
		}
	}

	void SetProperties(const FXLagObjectProperties& source);
};

