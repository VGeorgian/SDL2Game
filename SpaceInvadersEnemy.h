#pragma once
#include "Image.h"

class SpaceInvadersEnemy : public Image {
	int lifePoints;
public:
	SpaceInvadersEnemy();
	~SpaceInvadersEnemy();

	int GetLifePoints();
	void SetLifePoints(int points);
	int DecreaseLifePoints();

};