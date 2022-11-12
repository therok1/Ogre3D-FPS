#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>

#include "Collision.h"

class Projectile
{
public:

	Projectile();

	void init(Ogre::SceneManager* scnMgr);
	void update(float dt, const std::vector<Ogre::Entity*>& entities);
	void shoot(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Quaternion ori);
	void clear();

	static int bullets;

private:

	Ogre::ManualObject* createCubeMesh(const std::string& name, const std::string& matName);

	Ogre::SceneManager* m_scnMgr;
	Ogre::Entity* m_bullet;
	Ogre::SceneNode* m_bulletNode;

	Ogre::Vector3 m_velocity;
};

