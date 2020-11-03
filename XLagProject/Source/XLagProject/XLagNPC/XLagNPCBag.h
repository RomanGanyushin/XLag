#pragma once
#include <map>

class XLagNPCBag
{
public:
	void Put(const std::string& name, float quanity)
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

	float Take(const std::string& name, float quanity)
	{
		if (!HasItem(name))
			return 0.0f;

		auto result = std::min(quanity, Items[name]);
		Items[name] = Items[name] - result;
		
		if (Items[name] <= 0.0f)
		{
			Items.erase(Items.find(name));
		}
	}

	bool Has(const std::string& name, float quanity)
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
	std::map<std::string, float> Items;

private:
	bool HasItem(const std::string& name)
	{
		return Items.find(name) != Items.end();
	}
};