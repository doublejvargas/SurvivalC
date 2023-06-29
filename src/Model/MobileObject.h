#pragma once
#include "GameObject.h"

class MobileObject : protected GameObject
{
private:
	//KEY CHARACTERISTICS
	int m_Speed;
	int m_MaxHitPoints;

	//STATE VARIABLES
	int m_CurrentHitPoints;
	bool m_Alive;
	bool m_Busy;
	bool m_Fled;
	bool m_TurnOver; // Combat variable indicating if object's turn is over

	Vector2 m_PriorLocation;

public:
	//CONSTRUCTOR
	MobileObject(Game* game, const Vector2& pos, int speed, int maxHP);

	//Abstract methods to be implemented by animals and players, necessary for combat.
	virtual bool Flee() = 0;
	virtual bool Attack(MobileObject& target) = 0;
	
	//Remove speed from MobileObject object. If 0 set dead.
	void SufferHarm(int harm);

	//Getters
	inline int getSpeed() const { return m_Speed; }
	inline int getMaxHP() const { return m_MaxHitPoints; }
	inline int getCurrentHP() const { return m_CurrentHitPoints; }
	inline bool isAlive() const { return m_Alive; }
	inline bool isBusy() const { return m_Busy; }
	inline bool isFled() const { return m_Fled; }
	inline bool isTurnOver() const { return m_TurnOver; };
	inline Vector2 getPriorLoc() const { return m_PriorLocation; }

	//Setters
	inline void setCurrentHP(int currentHP) { m_CurrentHitPoints = currentHP; }
	inline void setAlive(bool alive) { m_Alive = alive; }
	inline void setBusy(bool busy) { m_Busy = busy; }
	inline void setFled(bool fled) { m_Fled = fled; }
	inline void setTurnOver(bool turnOver) { m_TurnOver = turnOver; }
	inline void setPriorLoc(const Vector2& priorLoc) { m_PriorLocation = priorLoc; }
};