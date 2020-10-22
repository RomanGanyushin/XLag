#pragma once

class XLagNPCTaskContext
{
public:
	int IndexForSubLevel(int subLevel)
	{
		EnsureVectorSize(subLevel);
		return ExecutingVector[subLevel];
	}

	void IncrementForSubLevel(int subLevel)
	{
		EnsureVectorSize(subLevel);
		ExecutingVector[subLevel] = ExecutingVector[subLevel] + 1;
	}

	const std::vector<int>& GetExecutingVector() const { return ExecutingVector; }

private:
	std::vector<int> ExecutingVector;

	inline void EnsureVectorSize(int size)
	{
		while (ExecutingVector.size() <= size)
		{
			ExecutingVector.push_back(0);
		}
	}
};