#pragma once

#include "MobileObject.h"
#include "Interfaces.h"
#include "AStarPathFinder.h"
#include "Texture.h"

#include <vector>

class Animal : protected MobileObject, public Interfaces::ITakesTurns, public Interfaces::IInteractable
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

	AStarPathFinder* m_PathFinder;

	Texture* m_GameTexture;
	Texture* m_CombatTexture;

	bool m_Remove;

public:
	Animal(Game* game, const Vector2& pos, uint32_t speed, uint32_t maxHP, uint32_t damage, std::vector<bool> canWalk, Texture* gameTex, Texture* combatTex);
	~Animal();

protected:
	void chooseNewPosition();

public:
	void wander();

	void interact(const Player& player) override;
	bool combatLogic(const MobileObject& target) override;
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

};