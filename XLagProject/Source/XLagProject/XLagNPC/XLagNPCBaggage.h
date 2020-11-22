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
	int32 Id;

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
		void Put(const TEnumAsByte<XLagDynamicObjectType> type, const int32 id, float quanity)
	{
		if (!HasItem(type, id))
		{
			FXLagBaggageItem newItem;
			newItem.ObjectType = type;
			newItem.Id = id;
			newItem.Quanity = quanity;
			Baggage.Items.Add(newItem);
		}
		else
		{
			FindItem(type, id).Quanity += quanity;
		}
	}

	UFUNCTION(BlueprintCallable)
		float Take(const TEnumAsByte<XLagDynamicObjectType> type, const int32 id, float quanity)
	{
		if (!HasItem(type, id))
			return 0.0f;

		auto &item = FindItem(type, id);

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
		bool HasQuanity(const TEnumAsByte<XLagDynamicObjectType> type, const int32 Id, float quanity)
	{
		if (!HasItem(type, Id))
			return false;

		return FindItem(type, Id).Quanity >= quanity;
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
		bool HasItem(const TEnumAsByte<XLagDynamicObjectType> type, const int32 id) const
	{
		return Baggage.Items.ContainsByPredicate([type, id](auto& it) {return it.ObjectType == type && it.Id == id; });
	}

	UFUNCTION(BlueprintCallable)
		FXLagBaggageItem& FindItem(const TEnumAsByte<XLagDynamicObjectType> type, const int32 id)
	{
		return *Baggage.Items.FindByPredicate([type, id](auto& it) {return it.ObjectType == type && it.Id == id; });
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FXLagBaggage Baggage;
};