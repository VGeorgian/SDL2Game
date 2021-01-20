#include "SpaceInvadersEnemy.h"

SpaceInvadersEnemy::SpaceInvadersEnemy(){
	lifePoints = 0;
}

SpaceInvadersEnemy::~SpaceInvadersEnemy() {

}

int SpaceInvadersEnemy::GetLifePoints() {
	return lifePoints;
}

void SpaceInvadersEnemy::SetLifePoints(int points) {
	lifePoints = points;
}
int SpaceInvadersEnemy::DecreaseLifePoints() {
	--lifePoints;
	return lifePoints;
}