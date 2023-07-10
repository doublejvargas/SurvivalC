#pragma once
#include "Game.h"
#include "MobileObject.h"
#include "Inventory.h"

class TerrainTile;
//class Game;

class Player : public MobileObject
{
public:
	enum ToolType { HAND, STAKE, ROCK, SPEAR };

private:
	//Player capabilities
	const int m_MaxWeight = 10;

	//Player state
	bool m_Hidden;
	bool m_Harvesting;
	bool m_Resting;
	bool m_CanRest;
	Game::Direction m_Facing = Game::NULLDIR;
	
	int m_StepsToday;
	int m_CyclesSinceRest;
	StationaryObject *m_CurrentRestObject = nullptr; //TODO how to identify/declare/cast this as an Irestable? ie. tree or base?
	Game* m_Game = nullptr;
	
	//Player's Items
	int m_NumSticks;
	Inventory* m_Inventory = nullptr;
	ToolType m_Tool = HAND;

	//Tentative -- prompts
	bool m_DisplayRestPrompt;
	bool m_DisplayUpgradePrompt;

public:
	Player(Map* map, const Vector2& pos, int maxHP, Game* game);
	~Player();

	//Scans the inventory for a specific type of food, and if it is found in inventory it is removed, and the player
	//heals by the food's given HP value
	void Eat(Food::FoodType type);

	// Combat Methods :
	//Flee - when the player attempts to flee from a carnivore they run the risk of failure.  This function flips a coin
	//       to determine whether the player is successful or not, sets "isFled" accordingly, and returns the player's
	//       success state in the form of a boolean
	//Attack - takes a target as a parameter, and flips a coin.  If the player is successful they deal damage to the
	//         target depending on their weapon.
	bool Flee() override;
	bool Attack(MobileObject& target) override;
	
	void AttemptMove(TerrainTile* T);
	void AttemptRest();

private:
	//Private internal methods/routines used by class
	void upgradeTool();
	bool spendSticks(int toSpend);
	void gatherSticks(int sticksHarvested);
	void heal(int HP);
	void takeStep();
	
	//
	bool checkForRestable();
	bool checkForBase();

public:
	//Getters
	inline int getStepsToday() const			{ return m_StepsToday; }
	inline int getSticks() const				{ return m_NumSticks; }
	inline ToolType getTool() const				{ return m_Tool; }
	inline bool isHidden() const				{ return m_Hidden; }
	inline bool isHarvesting() const			{ return m_Harvesting; }
	inline bool isResting()	const				{ return m_Resting; }
	inline bool isDisplayRestPrompt() const		{ return m_DisplayRestPrompt; }
	inline bool isDisplayUpgradesPrompt() const	{ return m_DisplayUpgradePrompt; }
	inline int getCyclesSinceRest() const		{ return m_CyclesSinceRest; }
	inline int getMaxWeigth() const				{ return m_MaxWeight; }
	inline Inventory* getInventory() const		{ return m_Inventory; }
	Game* getGame() const						{ return m_Game; }
	inline Game::Direction getFacing() const	{ return m_Facing; }

	//Setters
	inline void setStepsToday(int stepsToday)			{ m_StepsToday = stepsToday; }
	inline void setHidden(bool hidden)					{ m_Hidden = hidden;}
	inline void setHarvesting(bool harvesting)			{ m_Harvesting = harvesting; }
	inline void setResting(bool resting)				{ m_Resting = resting;}
	inline void setCyclesSinceRest(int cyclesSinceRest) { m_CyclesSinceRest = cyclesSinceRest; }
	void setGame(Game* game)							{ m_Game = game; }
	inline void setFacing(Game::Direction facing)		{ m_Facing = facing; }
	
	// Classes that will need access to certain private routines of player
	friend class Base;
	friend class RestingCombatEncounter;
	friend class Tree;
	friend class Rock;
	friend class Control;
};