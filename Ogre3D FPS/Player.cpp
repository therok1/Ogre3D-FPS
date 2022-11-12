#include "Player.h"

Player::Player() :
	m_scnMgr(nullptr),
	m_cam(nullptr),
	m_camNode(nullptr),
	m_camYawNode(nullptr),
	m_camPitchNode(nullptr),
	m_velocity(0, 0, 0),
	m_pivotPitch(0),
	m_start(SDL_GetTicks())
{
	m_bullets.reserve(20);
}

void Player::init(Ogre::SceneManager* scnMgr)
{
	m_scnMgr = scnMgr;

	m_camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	m_camNode->setPosition(0, 10, 0);

	m_camYawNode = m_camNode->createChildSceneNode();

	m_camPitchNode = m_camYawNode->createChildSceneNode();

	m_cam = scnMgr->createCamera("myCam");
	m_cam->setNearClipDistance(0.1f);
	m_cam->setAutoAspectRatio(true);
	m_camPitchNode->attachObject(m_cam);
}

void Player::update(float dt, const std::map<char, bool>& keys, const std::vector<Ogre::Entity*>& entities)
{
	if (keys.at(static_cast<char>(32)))
	{
		if ((SDL_GetTicks() - m_start) / 1000.0f > 0.2f)
		{
			m_start = SDL_GetTicks();

			std::unique_ptr<Projectile> bullet = std::make_unique<Projectile>();
			bullet->init(m_scnMgr);
			bullet->shoot(m_cam->getDerivedPosition(), m_cam->getDerivedOrientation() * Ogre::Vector3::NEGATIVE_UNIT_Z, m_cam->getDerivedOrientation());

			if (m_bullets.size() == 20)
			{
				m_bullets.front()->clear();
				m_bullets.erase(std::begin(m_bullets));
			}

			m_bullets.push_back(std::move(bullet));
		}
	}

	if (keys.at('w'))
	{
		m_velocity.z = -1;
	}

	if (keys.at('s'))
	{
		m_velocity.z = 1;
	}
	
	if (keys.at('a'))
	{
		m_velocity.x = -1;
	}

	if (keys.at('d'))
	{
		m_velocity.x = 1;
	}

	if ((!keys.at('w') && !keys.at('s')) || (keys.at('w') && keys.at('s')))
	{
		m_velocity.z = 0;
	}

	if ((!keys.at('a') && !keys.at('d')) || (keys.at('a') && keys.at('d')))
	{
		m_velocity.x = 0;
	}

	m_velocity.normalise();
	m_velocity *= dt * 50;

	Ogre::Vector3 newTranslation = m_camYawNode->getOrientation() * m_velocity;
	m_camNode->translate(newTranslation);

	for (auto& bullet : m_bullets)
	{
		bullet->update(dt, entities);
	}
}

bool Player::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
	m_camYawNode->yaw(Ogre::Degree(-0.05f * evt.xrel), Ogre::Node::TS_PARENT);

	float deltaPitch = -0.05f * evt.yrel;
	if (!(m_pivotPitch + deltaPitch > 65 && deltaPitch > 0) && !(m_pivotPitch + deltaPitch < -60 && deltaPitch < 0))
	{
		m_camPitchNode->pitch(Ogre::Degree(deltaPitch), Ogre::Node::TS_LOCAL);
		m_pivotPitch += deltaPitch;
	}

	return true;
}

Ogre::Camera* Player::getCam() const
{
	return m_cam;
}