#pragma once

#include "StationaryObject.h"
#include <random>

#define ENCOUNTER_CHANCE 65

class Tree : protected StationaryObject, public Interfaces::IRestable
{
private:
	unsigned int m_numSticks = 0;

public:
	Tree(Game* game, const Vector2& pos)
		: StationaryObject(game, pos, true)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 3);
		//range[1,4]
		m_numSticks = dis(gen) + 1; 
	}

	//TODO: finish implementing
	void interact(const Player& player) override
	{
		//player.gatherSticks(/*implement with lambda function here*/ [](void) {});
	}

	void restAt(const Player& player) override
	{
		//implement once game, player, carnivorefactory are implemented
	}
};