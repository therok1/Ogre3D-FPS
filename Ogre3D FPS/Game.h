#pragma once

#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <SDL.h>

#include <map>
#include <vector>
#include <memory>
#include <iostream>

#include "Player.h"

class Game : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:

	Game();

	void setup();
	void update(float dt);

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	bool keyReleased(const OgreBites::KeyboardEvent& evt);
	bool mouseMoved(const OgreBites::MouseMotionEvent& evt);

private:

	Ogre::ManualObject* createCubeMesh(const std::string& name, const std::string& matName);

	Ogre::Entity* m_cube, * m_cube1, * m_cube2;
	Ogre::Entity* m_ground;

	std::unique_ptr<Player> m_player;
	std::map<char, bool> m_keys;
	std::vector<Ogre::Entity*> m_entities;
};

