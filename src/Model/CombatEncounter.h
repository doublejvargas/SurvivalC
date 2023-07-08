#pragma once

#include <string>

class Player;
class Animal;
class Game;

class CombatEncounter
{

private:
	Player* m_Player = nullptr;
	Animal* m_Animal = nullptr;

	bool m_EncounterOver;
	bool m_PlayerTurn;
	bool m_AnimalTurn;

	bool m_DisplayMessage;
	std::string m_Message;

public:
	CombatEncounter(Player* player, Animal* animal);

	virtual void combatTurn();

private:
	//Private routines for the class
	void determineCombatOrder();
	void decodeMeats();

public:
	//Getters
	inline Player* getPlayer() const		{ return m_Player; }
	inline Animal* getAnimal() const		{ return m_Animal; }
	inline bool isEncounterOver() const		{ return m_EncounterOver; }
	inline bool isPlayerTurn() const		{ return m_PlayerTurn; }
	inline bool isAnimalTurn() const		{ return m_AnimalTurn; }
	inline bool isDisplayMessage() const	{ return m_DisplayMessage; }
	inline std::string getMessage() const	{ return m_Message; }
	//inline Game* getGame() const { return m_Game; }
	
	//Setters
	inline void setPlayer(Player* val)				{ m_Player = val; }
	inline void setAnimal(Animal* val)				{ m_Animal = val; }
	inline void setPlayerTurn(bool val)			{ m_PlayerTurn = val; }
	inline void setAnimalTurn(bool val)			{ m_AnimalTurn = val; }
	inline void setDisplayMessage(bool val)		{ m_DisplayMessage = val; }
	inline void setMessage(std::string val)		{ m_Message = val; }
	//inline void setGame(Game* val)			{ m_Game = val; }
	//inline void setEncounterOver(bool val) { m_EncounterOver = val; }
	
	friend class RestingCombatEncounter;
};