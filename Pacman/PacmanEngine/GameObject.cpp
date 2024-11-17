#include "GameObject.h"

pac::GameObject::GameObject() : ticksSinceLastMove(0)
{
}

uint64_t pac::GameObject::GetTicksSinceLastMove()
{
	return this->ticksSinceLastMove;
}

pac::Position pac::GameObject::GetPosition()
{
	return this->position;
}

pac::Direction pac::GameObject::GetDirection()
{
	return this->direction;
}