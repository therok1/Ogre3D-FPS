#include "Collision.h"

bool Collision::entity(Ogre::Entity* entityA, Ogre::Entity* entityB)
{
	if (entityA->isAttached() && entityB->isAttached())
	{
		return entityA->getWorldBoundingBox().intersects(entityB->getWorldBoundingBox());
	}
	
	return false;
}
