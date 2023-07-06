#pragma once

#include "Player.h"
#include "Animal.h"
#include "Map.h"

typedef unsigned int uint32_t;

class Game
{
public:
	// Global Play parameters of game
	static const uint32_t MAX_ANIMALS = 5;
	static const uint32_t WIDTH = 5;
	static const uint32_t HEIGHT = 5;
	static const uint32_t STEPS_PER_CYCLE = 5;
	static const uint32_t DAYS_TO_SURVIVE = 5;

	enum Direction { RIGHT, LEFT, UP, DOWN };

private:
	// Game states
	bool m_DayTime;
	bool m_InCombat;
	bool m_GameWon;
	bool m_GameOver;
	bool m_AnimalTaggedForRemoval;
	uint32_t m_Day;

	// Mobile game objects
	Player* m_Player = nullptr;
	std::vector<Animal*> m_Animals;
	
	// Stationary game objects
	//Base m_Base;
	
	// Referenced when game is in combat mode 
	//CombatEncounter m_CombatEncounter;

	// Defines placement of TerrainTiles and StationaryObjects
	Map* m_Map = nullptr;

	// "Factories" for instantiation of new animals
	//HerbivoreFactory m_HerbFact;
	//CarnivoreFactory m_CarnFact;

	// Needed for opengl stuff
	Loader* m_Loader = nullptr;

public:
	// Default constructor for the game. Sets up game state variables, creates a new map, places the player and
	// the base, and reveals the tiles the player can currently see on the miniMap
	Game(Loader* loader);

	void checkForEncounter();
	void spawnNewHerbivore();
	void spawnNewCarnivore();
	Vector2 spawnNewAnimalLocation();
	void despawnDistantAnimals();
	void clearAllAnimals();
	void checkDayCycle();
	void mapRevealAfterFlee();

private:
	void placePlayerAndBase();
	void clearBrush();
	void initMapReveal();

public:
	// Getters
	inline bool isGameOver() const					{ return m_GameOver; }
	inline bool isGameWon() const					{ return m_GameWon; }
	inline bool isDayTime() const					{ return m_DayTime; }
	inline int getDay() const						{ return m_Day; }
	inline bool isInCombat() const					{ return m_InCombat; }
	inline bool isAnimalTaggedForRemoval() const	{ return m_AnimalTaggedForRemoval; }
	inline Player* getPlayer() const				{ return m_Player; }
	inline std::vector<Animal*> getAnimals() const	{ return m_Animals; }
	inline Map* getMap() const						{ return m_Map; }
	inline Loader* getLoader() const				{ return m_Loader; }
	//inline Base getBase() { return base; }
	//inline CombatEncounter getCurrentEncounter() { return m_CurrentEncounter; }


	// Setters
	inline void setGameOver(bool gameOver) { m_GameOver = gameOver; }
	inline void setGameWon(bool gameWon) { m_GameWon = gameWon; }
	inline void setInCombat(bool inCombat) { inCombat = m_InCombat; }
	inline void setAnimalTaggedForRemoval(bool tag ) { m_AnimalTaggedForRemoval = tag; }
	//inline void setCurrentEncounter(CombatEncounter currentEncounter) { this.currentEncounter = currentEncounter; }

	

};
