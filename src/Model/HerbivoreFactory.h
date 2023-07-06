#pragma once

#include "Herbivore.h"
#include "Loader.h"

class HerbivoreFactory
{

	static Herbivore ProduceHerbivore(Map* map, const Vector2& pos, Herbivore::HERBIVORE_TYPE type, Loader* loader)
	{
		std::vector<bool> canWalk(3, false);
		Texture gameTex, combatTex;

		if (type == Herbivore::RABBIT)
		{
			canWalk = { true, true, false };
			gameTex = loader->LoadTexture("res/textures/rabbit.png");
			combatTex = loader->LoadTexture("res/textures/rabbit-pixelized.png");
			return Herbivore(map, pos, 1, 1, 0, canWalk, &gameTex, &combatTex, Herbivore::RABBIT);
		}

		else if (type == Herbivore::DEER)
		{
			canWalk = { true, false, false };
			gameTex = loader->LoadTexture("res/textures/deer.png");
			combatTex = loader->LoadTexture("res/textures/deer-pixelized.png");
			return Herbivore(map, pos, 1, 3, 0, canWalk, &gameTex, &combatTex, Herbivore::DEER);
		}

		else if (type == Herbivore::FISH)
		{
			canWalk = { false, false, true };
			gameTex = loader->LoadTexture("res/textures/fish.png");
			combatTex = loader->LoadTexture("res/textures/fish-pixelized.png");
			return Herbivore(map, pos, 1, 1, 0, canWalk, &gameTex, &combatTex, Herbivore::FISH);
		}

		else
		{
			canWalk = { false, false, false };
			gameTex = loader->LoadTexture("");
			combatTex = loader->LoadTexture("");
			return Herbivore(map, pos, 0, 0, 0, canWalk, &gameTex, &combatTex, Herbivore::NULLHERBIVORE);
		}
	}
};