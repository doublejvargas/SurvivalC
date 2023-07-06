#pragma once

#include "Carnivore.h"
#include "Loader.h"

class CarnivoreFactory
{

	static Carnivore ProduceCarnivore(Map* map, const Vector2& pos, Carnivore::CARNIVORE_TYPE type, Loader* loader)
	{
		std::vector<bool> canWalk(3, false);
		Texture gameTex, combatTex;
		
		if (type == Carnivore::WOLF)
		{
			canWalk = { true, true, false };
			gameTex = loader->LoadTexture("res/textures/wolf.png");
			combatTex = loader->LoadTexture("res/textures/wolf-pixelized.png");
			return Carnivore(map, pos, 2, 2, 3, canWalk, &gameTex, &combatTex, Carnivore::WOLF);
		}

		else if (type == Carnivore::LION)
		{
			canWalk = { true, true, false };
			gameTex = loader->LoadTexture("res/textures/lion.png");
			combatTex = loader->LoadTexture("res/textures/lion-pixelized.png");
			return Carnivore(map, pos, 2, 8, 4, canWalk, &gameTex, &combatTex, Carnivore::LION);
		}

		else if (type == Carnivore::CROCODILE)
		{
			canWalk = { false, false, false };
			gameTex = loader->LoadTexture("res/textures/lion.png");
			combatTex = loader->LoadTexture("res/textures/lion-pixelized.png");
			return Carnivore(map, pos, 2, 5, 3, canWalk, &gameTex, &combatTex, Carnivore::CROCODILE);
		}

		else
		{
			canWalk = { false, false, false };
			gameTex = loader->LoadTexture("");
			combatTex = loader->LoadTexture("");
			return Carnivore(map, pos, 0, 0, 0, canWalk, &gameTex, &combatTex, Carnivore::NULLCARNIVORE);
		}
	}
};