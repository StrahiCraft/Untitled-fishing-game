#include "ReelingIn.h"

void ReelingIn::onStateEnter()
{

}

void ReelingIn::onStateUpdate(float deltaTime)
{
	_player->update(deltaTime);
	_fish->setPosition(_player->getPosition());
}
