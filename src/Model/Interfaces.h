#pragma once

#include "Player.h"
#include "MobileObject.h"

// This header file contains a namespace that holds all the interfaces that some derived classes will make use of
namespace Interfaces
{
	class IInteractable
	{
	public:
		virtual void interact(const Player& player) = 0; // should this be a const ref? or is player modified?
	};

	class IRestable
	{
	public:
		virtual void restAt(const Player& player) = 0;
	};

	class ITakesTurns
	{
	public:
		// Parameter target isn't necessarily used in all combat logic implementations, but it is essential for a subset of them
		virtual bool combatLogic(const MobileObject& target) = 0;
	};
}