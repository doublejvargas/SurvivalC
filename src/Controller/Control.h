#pragma once

#include "Game.h"

class Control 
{
private:
	bool m_rightKeyDown;
	bool m_leftKeyDown;
	bool m_upKeyDown;
	bool m_downKeyDown;

	bool m_GameWasInCombat;
	bool m_ResetListeners;

	Player* m_Player;

public:
	Control(Player* player);

private:
	void onUpdate();
	void update();
	TerrainTile* targetPos();
	void revealMiniMap(Game::Direction facing);
	void setUpListeners();

public:
	inline void setDownKeyDown(bool isDown)		{ m_downKeyDown = isDown; }
	inline void setLeftKeyDown(bool isDown)		{ m_leftKeyDown = isDown; }
	inline void setRightKeyDown(bool isDown)	{ m_rightKeyDown = isDown; }
	inline void setUpKeyDown(bool isDown)		{ m_upKeyDown = isDown; }

};
