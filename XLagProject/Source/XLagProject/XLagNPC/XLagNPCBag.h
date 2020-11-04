#pragma once
#include <map>

class XLagNPCBag
{
public:
	void Put(const FString& name, float quanity)
	{
		if (!HasItem(name))
		{
			Items[name] = quanity;
		}
		else
		{
			Items[name]+= quanity;
		}
	}

	float Take(const FString& name, float quanity)
	{
		if (!HasItem(name))
			return 0.0f;

		auto result = std::min(quanity, Items[name]);
		Items[name] = Items[name] - result;
		
		if (Items[name] <= 0.0f)
		{
			Items.erase(Items.find(name));
			return 0.0f;
		}

		return result;
	}

	bool Has(const FString& name, float quanity)
	{
		if (!HasItem(name))
			return false;

		return Items[name] >= quanity;
	}

	void Reset()
	{
		Items.clear();
	}

protected:
	std::map<FString, float> Items;

private:
	bool HasItem(const FString& name)
	{
		return Items.find(name) != Items.end();
	}
};