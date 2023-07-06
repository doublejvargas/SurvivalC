#pragma once

#include "Interfaces.h"
#include "MobileObject.h"
#include <vector>


class Game;
class AStarPathFinder;
class Texture;

class Game;

class Animal : public MobileObject, public Interfaces::ITakesTurns, public Interfaces::IInteractable
{
private:
	bool m_CanWalkGrass;
	bool m_CanWalkDesert;
	bool m_CanWalkWater;

	uint32_t m_Damage;

	Vector2 m_TargetPos;
	std::vector<Vector2> m_CurrentPath;
	uint32_t m_PathIndex;
	bool m_PathCompleted;

	AStarPathFinder* m_PathFinder = nullptr;

	Texture* m_GameTexture = nullptr;
	Texture* m_CombatTexture = nullptr;

	bool m_Remove;

public:
	Animal(Map* map, const Vector2& pos, int speed, uint32_t maxHP, uint32_t damage, const std::vector<bool>& canWalk, Texture* gameTex, Texture* combatTex);
	~Animal();

private:
	virtual void chooseNewPosition(const Player& player);

public:
	void wander(Game* game);

	void interact(const Player& player) override;
	bool combatLogic(MobileObject& target) override;
	bool Flee() override;
	bool Attack(MobileObject& target) override;

	inline bool canWalkGrass() const			{ return m_CanWalkGrass; }
	inline bool canWalkDesert() const			{ return m_CanWalkDesert; }
	inline bool canWalkWater() const			{ return m_CanWalkWater; }
	inline Texture* getCombatTexture() const	{ return m_CombatTexture; }
	inline Texture* getGameTexture() const		{ return m_GameTexture; }
	inline bool isRemove() const				{ return m_Remove; }

	inline void setTargetPos(const Vector2& targetPos) { m_TargetPos = targetPos; }
	inline void setRemove(bool remove) { m_Remove = remove; }


	friend class Carnivore;
};