#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player() : Actor() {}
	Player(float x, float y, float collisionRadius, const char* spriteFilePath);
	void update(float deltatime) override;
	void debug() override;
};

