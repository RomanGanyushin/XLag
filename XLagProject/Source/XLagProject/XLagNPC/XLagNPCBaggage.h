#pragma once
#include "../XLagDynamicObject/XLagDynamicObjectType.h"
#include "XLagNPCBaggage.generated.h"

USTRUCT(BlueprintType)
struct FXLagNPCBaggageItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	TEnumAsByte<XLagDynamicObjectType> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
	float Quanity;
};

USTRUCT(BlueprintType)
struct FXLagNPCBaggage
{
	GENERATED_BODY()

	void Put(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name, float quanity)
	{
		if (!HasItem(type, name))
		{
			FXLagNPCBaggageItem newItem;
			newItem.ObjectType = type;
			newItem.Name = name;
			newItem.Quanity = quanity;
			Items.Add(newItem);
		}
		else
		{
			FindItem(type, name).Quanity += quanity;
		}
	}

	float Take(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name, float quanity)
	{
		if (!HasItem(type, name))
			return 0.0f;

		auto &item = FindItem(type, name);

		auto result = std::min(quanity, item.Quanity);
		item.Quanity -= result;
		
		if (item.Quanity <= 0.0f)
		{
			auto removeIndex = Items.IndexOfByPredicate([&item](auto&it) {return &it == &item; });
			Items.RemoveAt(removeIndex);
		}

		return result;
	}

	bool Has(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name, float quanity)
	{
		if (!HasItem(type, name))
			return false;

		return FindItem(type, name).Quanity >= quanity;
	}

	void Reset(const TEnumAsByte<XLagDynamicObjectType> type)
	{
		auto removeIndex = Items.IndexOfByPredicate([type](auto&it) {return it.ObjectType == type; });
		Items.RemoveAt(removeIndex);
	}

	bool HasItem(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name) const
	{
		return Items.ContainsByPredicate([type, name](auto& it) {return it.ObjectType == type && it.Name == name; });
	}

	FXLagNPCBaggageItem& FindItem(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name)
	{
		return *Items.FindByPredicate([type, name](auto& it) {return it.ObjectType == type && it.Name == name; });
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
		TArray<FXLagNPCBaggageItem> Items;
};