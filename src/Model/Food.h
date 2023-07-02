#pragma once

typedef unsigned int uint32_t;

class Food
{
public:
	enum FoodType { Berries, Rabbit, Deer, Fish, Wolf, Lion, Crocodile, FOOD_NULL };

private:
	FoodType m_FoodType;
	uint32_t m_HPValue;
	uint32_t m_Weight;

public:
	Food(FoodType foodType)
		: m_FoodType(foodType)
	{
		setValues();
	}

	// Default constructor
	Food()
		: m_FoodType(FOOD_NULL), m_HPValue(0), m_Weight(0)
	{
	}

	inline FoodType getFoodType() const { return m_FoodType; }
	inline uint32_t getHPValue() const { return m_HPValue; }
	inline uint32_t getWeigth() const { return m_Weight; }

private:
	void setValues()
	{
		switch (getFoodType())
		{
		case Rabbit:
			m_HPValue = 3;
			m_Weight = 2;
			break;
		case Deer:
			m_HPValue = 4;
			m_Weight = 2;
			break;
		case Fish:
			m_HPValue = 1;
			m_Weight = 1;
			break;
		case Wolf:
			m_HPValue = 4;
			m_Weight = 2;
			break;
		case Lion:
			m_HPValue = 6;
			m_Weight = 2;
			break;
		case Crocodile:
			m_HPValue = 5;
			m_Weight = 3;
			break;
		case FOOD_NULL:
			m_HPValue = 0;
			m_Weight = 0;
			break;
		default:
			m_HPValue = 1;
			m_Weight = 2;
			break;
		}
	}
};