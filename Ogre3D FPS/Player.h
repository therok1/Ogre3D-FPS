#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <SDL.h>

#include "Projectile.h"

#include <map>
#include <vector>
#include <memory>
#include <iostream>

class Player
{
public:

	Player();

	void init(Ogre::SceneManager* scnMgr);
	void update(float dt, const std::map<char, bool>& keys, const std::vector<Ogre::Entity*>& entities);
	bool mouseMoved(const OgreBites::MouseMotionEvent& evt);

	Ogre::Camera* getCam() const;

private:

	Ogre::SceneManager* m_scnMgr;

	Ogre::Camera* m_cam;
	Ogre::SceneNode* m_camNode;
	Ogre::SceneNode* m_camYawNode;
	Ogre::SceneNode* m_camPitchNode;

	Ogre::Vector3 m_velocity;

	std::vector<std::unique_ptr<Projectile>> m_bullets;

	float m_pivotPitch;

	Uint32 m_start;

};

