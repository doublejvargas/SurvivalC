#include "Inventory.h"

Inventory::Inventory()
{ }

Inventory::Inventory(uint32_t maxWeight)
{
	m_MaxWeight = maxWeight;
	m_NumBerries = 0;
	m_NumRabbits = 0;
	m_NumDeer = 0;
	m_NumFish= 0;
	m_NumWolves = 0;
	m_NumLions = 0;
	m_NumCrocodiles = 0;
	m_CurrentWeight = 0;
}

void Inventory::InsertFood(Food::FoodType foodType)
{
	Food food(foodType);
	m_Contents.push_back(food);
	m_CurrentWeight += food.getWeigth();

	if (m_CurrentWeight > m_MaxWeight)
		TraceBack(BuildTable());
	else
		UpdateValue(food, 1);
}

Food Inventory::RemoveFood(Food::FoodType foodType)
{
	std::vector<Food>::iterator it;
	for (it = m_Contents.begin(); it != m_Contents.end(); it++)
	{
		if (it->getFoodType() == foodType)
		{
			m_Contents.erase(it);
			UpdateValue(*it, -1);
			m_CurrentWeight -= it->getWeigth();
			return *it;
		}
	}

	fprintf(stderr, "That food type is not in inventory!\n");
	return Food();
}

void Inventory::UpdateValue(Food food, int i)
{
	switch (food.getFoodType())
	{
	case Food::FoodType::Rabbit:
		m_NumRabbits += i;
		break;
	case Food::FoodType::Deer:
		m_NumDeer += i;
		break;
	case Food::FoodType::Fish:
		m_NumFish += i;
		break;
	case Food::FoodType::Wolf:
		m_NumWolves += i;
		break;
	case Food::FoodType::Lion:
		m_NumLions += i;
		break;
	case Food::FoodType::Crocodile:
		m_NumCrocodiles += i;
		break;
	default:
		m_NumBerries += i;
	}
}

void Inventory::UpdateAllFoodValues()
{
	m_NumBerries = 0;
	m_NumRabbits = 0;
	m_NumDeer = 0;
	m_NumFish = 0;
	m_NumWolves = 0;
	m_NumLions = 0;
	m_NumCrocodiles = 0;

	for (Food food : m_Contents)
		UpdateValue(food, 1);
}

//BuildTable implements the KnapSack Problem to keep order in the weight of the inventory
std::vector<std::vector<int>> Inventory::BuildTable()
{
	size_t n = m_Contents.size();
	//initializing 2D vector of size (n + 1) x (max weight + 1)
	std::vector<std::vector<int>> B(n + 1, std::vector<int>(m_MaxWeight + 1, 0));

	for (uint32_t i = 0; i <= n; i++)				// Looping through items in inventory
	{
		for (uint32_t k = 0; k <= m_MaxWeight; k++) // Looping through 0 -> m_MaxWeight
		{
			if (i == 0 || k == 0)
				B[i][k] = 0;						// Initialize base cases
			else
			{
				auto food = m_Contents.at(i - 1);
				if (food.getWeigth() <= k)			// if current item can be in the solution
					B[i][k] = max(food.getHPValue() + B[i - 1][k - food.getWeigth()], B[i - 1][k]);
				else
					B[i][k] = B[i - 1][k];		
			}
		}
	}

	return B;
}

void Inventory::TraceBack(std::vector<std::vector<int>> table)
{
	size_t i = m_Contents.size();
	uint32_t k = m_MaxWeight;

	while (i > 0 && m_MaxWeight > 0)
	{
		if (table[i][k] != table[i - 1][k])
		{
			k = k - m_Contents.at(i - 1).getWeigth();
			i--;
		}
		else
		{
			m_CurrentWeight -= m_Contents.at(i - 1).getWeigth();
			m_Contents.erase(m_Contents.begin() + (i - 1));
			i--;
		}
	}

	UpdateAllFoodValues();
}

