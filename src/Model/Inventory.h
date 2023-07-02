#pragma once

#include "Food.h"
#include <vector>

//typedef unsigned int uint32_t;

class Inventory
{
private:
	uint32_t m_NumBerries;
	uint32_t m_NumRabbits;
	uint32_t m_NumDeer;
	uint32_t m_NumFish;
	uint32_t m_NumWolves;
	uint32_t m_NumLions;
	uint32_t m_NumCrocodiles;
	uint32_t m_CurrentWeight;
	uint32_t m_MaxWeight;

	std::vector<Food> m_Contents;

public:
	Inventory();
	Inventory(uint32_t maxWeight);

	void InsertFood(Food::FoodType foodType);
	Food RemoveFood(Food::FoodType foodType);
	void UpdateValue(Food food, int i);
	void UpdateAllFoodValues();

private:
	//private routines that aid in functionality of the inventory
	inline int max(int a, int b) { return (a > b) ? a : b; }
	std::vector<std::vector<int>> BuildTable();
	void TraceBack(std::vector<std::vector<int>> table);

public:
	//Getters
	inline int getNumBerries()				{ return m_NumBerries; }
	inline int getNumRabbits()				{ return m_NumRabbits; }
	inline int getNumDeer()					{ return m_NumDeer; }
	inline int getNumFish()					{ return m_NumFish; }
	inline int getNumWolves()				{ return m_NumWolves; }
	inline int getNumLions()				{ return m_NumLions; }
	inline int getNumCrocodiles()			{ return m_NumCrocodiles; }
	inline int getCurrentWeight()			{ return m_CurrentWeight; }
	inline int getMaxWeight()				{ return m_MaxWeight; }
	inline std::vector<Food> getContents()	{ return m_Contents; }

};
