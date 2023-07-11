#include "Control.h"
#include "Player.h"
#include "Base.h"
#include <GLFW/glfw3.h>
#include <stdexcept>

Control::Control(Player* player)
{
	m_Player = player;
	m_GameWasInCombat = false;
	m_ResetListeners = false;
	setUpListeners();
	onUpdate();
}

void Control::onUpdate() // might rename to OnUpdate or OnRender
{
	setUpListeners(); //experimental
	if (m_ResetListeners)
	{
		m_Player->getGame()->mapRevealAfterFlee();
		setUpListeners();
		m_upKeyDown = false;
		m_downKeyDown = false;
		m_rightKeyDown = false;
		m_leftKeyDown = false;
		m_ResetListeners = false;
	}
	update();
}

void Control::update()
{
	if (!m_Player->isBusy() && !m_Player->getGame()->isInCombat())
	{
		if (m_GameWasInCombat)
		{
			m_ResetListeners = true;
			m_GameWasInCombat = false;
		}
		
		if (m_upKeyDown)
		{
			m_Player->setFacing(Game::UP);
			m_Player->AttemptMove(targetPos());
			revealMiniMap(m_Player->getFacing());
			//m_Player->getGame()->checkForEncounter();
		}
		else if (m_downKeyDown)
		{
			m_Player->setFacing(Game::DOWN);
			m_Player->AttemptMove(targetPos());
			revealMiniMap(m_Player->getFacing());
			//m_Player->getGame()->checkForEncounter();
		}
		else if (m_rightKeyDown)
		{
			m_Player->setFacing(Game::RIGHT);
			m_Player->AttemptMove(targetPos());
			revealMiniMap(m_Player->getFacing());
			//m_Player->getGame()->checkForEncounter();
		}
		else if (m_leftKeyDown)
		{
			m_Player->setFacing(Game::LEFT);
			m_Player->AttemptMove(targetPos());
			revealMiniMap(m_Player->getFacing());
			//m_Player->getGame()->checkForEncounter();
		}

		m_Player->getGame()->despawnDistantAnimals();
		m_Player->getGame()->checkDayCycle();

		if (!m_Player->isAlive())
		{
			m_Player->getGame()->setGameOver(true);
			m_Player->getGame()->setGameWon(false);
		}
		else
		{
			if (m_Player->getGame()->getDay() == Game::DAYS_TO_SURVIVE)
			{
				m_Player->getGame()->setGameOver(true);
				m_Player->getGame()->setGameWon(true);
			}
		}
	}
	if (m_Player->getGame()->isInCombat())
		m_GameWasInCombat = true;
	else
	{
		std::vector<Animal*> animals = m_Player->getGame()->getAnimals();
		for (Animal* animal : animals)
		{
			if (!animal->isBusy())
				animal->wander(m_Player->getGame()); // a bit redundant here. wander needs game to retrieve player position. might want to consider changing this.
		}
	}
}

TerrainTile* Control::targetPos()
{
	int y = (int)m_Player->getPosition().v0();
	int x = (int)m_Player->getPosition().v1();
	try
	{
		switch (m_Player->getFacing())
		{
		case Game::UP:
			return &m_Player->getGame()->getMap()->getTerrainTiles().at(y - 1).at(x);
		case Game::DOWN:
			return &m_Player->getGame()->getMap()->getTerrainTiles().at(y + 1).at(x);
		case Game::LEFT:
			return &m_Player->getGame()->getMap()->getTerrainTiles().at(y).at(x - 1);
		case Game::RIGHT:
			return &m_Player->getGame()->getMap()->getTerrainTiles().at(y).at(x + 1);
		default:
			return &m_Player->getGame()->getMap()->getTerrainTiles().at(y).at(x);

		}
	}
	catch (const std::out_of_range& e)
	{
		fprintf(stderr, "control.cpp/targetPos exception. pos: (%d, %d) y,x. err: %s\n", y, x, e.what());
		return nullptr;
	}
}

void Control::revealMiniMap(Game::Direction facing)
{
	int playerPosY = (int)m_Player->getPosition().v0();
	int playerPosX = (int)m_Player->getPosition().v1();
	switch (facing)
	{
	case Game::UP:
		for (int x = playerPosX - 10; x <= playerPosX + 10; x++)
		{
			playerPosY = (int)m_Player->getPosition().v0();
			playerPosX = (int)m_Player->getPosition().v1();
			try {
				m_Player->getGame()->getMap()->getTerrainTiles().at(playerPosY - 10).at(x).setIsRevealedOnMiniMap(true);
			}	
			catch (const std::out_of_range& e) {
				fprintf(stderr, "reveal minimap exception. pos: (%d, %d). err: %s\n", playerPosY - 10, x, e.what());
			}
		}
		break;
	case Game::DOWN:
		for (int x = playerPosX - 10; x <= playerPosX + 10; x++)
		{
			playerPosY = (int)m_Player->getPosition().v0();
			playerPosX = (int)m_Player->getPosition().v1();
			try {
				m_Player->getGame()->getMap()->getTerrainTiles().at(playerPosY + 10).at(x).setIsRevealedOnMiniMap(true);
			}
			catch (const std::out_of_range& e) {
				fprintf(stderr, "reveal minimap exception. pos: (%d, %d) y,x. err: %s\n", playerPosY + 10, x, e.what());
			}
		}
		break;
	case Game::LEFT:
		for (int y = playerPosY - 10; y <= playerPosY + 10; y++)
		{
			playerPosY = (int)m_Player->getPosition().v0();
			playerPosX = (int)m_Player->getPosition().v1();
			try {
				m_Player->getGame()->getMap()->getTerrainTiles().at(y).at(playerPosX - 10).setIsRevealedOnMiniMap(true);
			}
			catch (const std::out_of_range& e) {
				fprintf(stderr, "reveal minimap exception. pos: (%d, %d). err: %s\n", y, playerPosX - 10, e.what());
			}
		}
		break;
	case Game::RIGHT:
		for (int y = playerPosY - 10; y <= playerPosY + 10; y++)
		{
			playerPosY = (int)m_Player->getPosition().v0();
			playerPosX = (int)m_Player->getPosition().v1();
			try {
				m_Player->getGame()->getMap()->getTerrainTiles().at(y).at(playerPosX + 10).setIsRevealedOnMiniMap(true);
			}
			catch (const std::out_of_range& e) {
				fprintf(stderr, "reveal minimap exception. pos: (%d, %d). err: %s\n", y, playerPosX + 10, e.what());
			}
		}
		break;
	}
}

void Control::setUpListeners()
{
	//key pressed
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		printf("pressed up!\n");
		setUpKeyDown(true);
	}
		

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
		setDownKeyDown(true);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		setRightKeyDown(true);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS)
		setLeftKeyDown(true);

	//key released
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_RELEASE)
		setUpKeyDown(false);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_RELEASE)
		setDownKeyDown(false);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_RELEASE)
		setRightKeyDown(false);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_RELEASE)
		setLeftKeyDown(false);

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_RELEASE)
		m_Player->AttemptRest();

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_B) == GLFW_RELEASE)
	{
		if (m_Player->checkForBase())
			m_Player->getGame()->getBase()->buyNewBaseUpgrade(m_Player);
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_T) == GLFW_RELEASE)
	{
		if (m_Player->checkForBase())
			m_Player->getGame()->getBase()->buyNewToolUpgrade(m_Player);
	}
}

