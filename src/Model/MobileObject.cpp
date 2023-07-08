#include "MobileObject.h"

MobileObject::MobileObject(Map* map, const Vector2& pos, int speed, int maxHP) : GameObject(pos), m_Speed(speed), m_PriorLocation(Vector2(getPosition().v0(), getPosition().v1()))
{
	m_MaxHitPoints = maxHP;
	m_CurrentHitPoints = maxHP;
	m_Alive = true;
	m_Busy = false;
	m_TurnOver = false;
	m_Fled = false;
	m_Map = map;
}

void MobileObject::SufferHarm(int harm)
{
	setCurrentHP(getCurrentHP() - harm);
	if (getCurrentHP() <= 0)
	{
		setCurrentHP(0);
		setAlive(false);
	}
}
