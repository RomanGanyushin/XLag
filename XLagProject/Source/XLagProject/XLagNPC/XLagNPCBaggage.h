#pragma once
#include "../XLagDynamicObject/XLagDynamicObjectType.h"
#include "XLagNPCBaggage.generated.h"

USTRUCT(BlueprintType)
struct FXLagBaggageItem
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
struct FXLagBaggage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame)
		TArray<FXLagBaggageItem> Items;
};

UCLASS() 
class UXLagNPCBaggage : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void Put(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name, float quanity)
	{
		if (!HasItem(type, name))
		{
			FXLagBaggageItem newItem;
			newItem.ObjectType = type;
			newItem.Name = name;
			newItem.Quanity = quanity;
			Baggage.Items.Add(newItem);
		}
		else
		{
			FindItem(type, name).Quanity += quanity;
		}
	}

	UFUNCTION(BlueprintCallable)
		float Take(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name, float quanity)
	{
		if (!HasItem(type, name))
			return 0.0f;

		auto &item = FindItem(type, name);

		auto result = std::min(quanity, item.Quanity);
		item.Quanity -= result;

		if (item.Quanity <= 0.0f)
		{
			auto removeIndex = Baggage.Items.IndexOfByPredicate([&item](auto&it) {return &it == &item; });
			Baggage.Items.RemoveAt(removeIndex);
		}

		return result;
	}

	UFUNCTION(BlueprintCallable)
		bool HasQuanity(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name, float quanity)
	{
		if (!HasItem(type, name))
			return false;

		return FindItem(type, name).Quanity >= quanity;
	}

	UFUNCTION(BlueprintCallable)
		bool HasObject(const TEnumAsByte<XLagDynamicObjectType> type)
	{
		return Baggage.Items.ContainsByPredicate([type](auto& it) {return it.ObjectType == type; });
	}

	UFUNCTION(BlueprintCallable)
		void Reset(const TEnumAsByte<XLagDynamicObjectType> type)
	{
		auto removeIndex = Baggage.Items.IndexOfByPredicate([type](auto&it) {return it.ObjectType == type; });
		Baggage.Items.RemoveAt(removeIndex);
	}

	UFUNCTION(BlueprintCallable)
		bool HasItem(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name) const
	{
		return Baggage.Items.ContainsByPredicate([type, name](auto& it) {return it.ObjectType == type && it.Name == name; });
	}

	UFUNCTION(BlueprintCallable)
		FXLagBaggageItem& FindItem(const TEnumAsByte<XLagDynamicObjectType> type, const FString& name)
	{
		return *Baggage.Items.FindByPredicate([type, name](auto& it) {return it.ObjectType == type && it.Name == name; });
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FXLagBaggage Baggage;
};