#include "Projectile.h"

#include "Player.h"

Projectile::Projectile() :
	m_scnMgr(nullptr),
	m_bullet(nullptr),
	m_bulletNode(nullptr),
	m_velocity(0, 0, 0)
{

}

void Projectile::init(Ogre::SceneManager* scnMgr)
{
	m_scnMgr = scnMgr;

	m_bullet = scnMgr->createEntity("bullet" + std::to_string(bullets), "cube1.mesh");
	m_bulletNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	m_bulletNode->setScale(0.5f, 0.5f, 3.0f);
	m_bulletNode->attachObject(m_bullet);

	bullets++;
}

void Projectile::update(float dt, const std::vector<Ogre::Entity*>& entities)
{
	m_velocity.normalise();
	m_velocity.y += -9.8f * 0.02f * dt;
	m_velocity *= dt * 100.0f;

	for (auto& entity : entities)
	{
		if (Collision::entity(m_bullet, entity) || m_bulletNode->getPosition().y <= 0)
		{
			m_velocity = Ogre::Vector3::ZERO;

			return;
		}
	}

	m_bulletNode->translate(m_velocity);
	m_bulletNode->lookAt(m_bulletNode->getPosition() + m_velocity, Ogre::Node::TS_WORLD);
}

void Projectile::shoot(Ogre::Vector3 pos, Ogre::Vector3 dir, Ogre::Quaternion ori)
{
	m_bulletNode->setPosition(pos + Ogre::Vector3(0, -2, 0));
	m_bulletNode->setOrientation(ori);
	
	m_velocity = dir;
}

void Projectile::clear()
{
	m_bulletNode->detachAllObjects();
	m_bulletNode->removeAndDestroyAllChildren();
	m_scnMgr->destroySceneNode(m_bulletNode);
	m_scnMgr->destroyEntity(m_bullet);
}

Ogre::ManualObject* Projectile::createCubeMesh(const std::string& name, const std::string& matName)
{
	Ogre::ManualObject* cube = new Ogre::ManualObject(name);

	cube->begin(matName);

	cube->position( 0.5f, -0.5f,  1.0f); cube->normal( 0.408248f, -0.816497f,  0.408248f); cube->textureCoord(1.0f, 0.0f);
	cube->position(-0.5f, -0.5f,  0.0f); cube->normal(-0.408248f, -0.816497f, -0.408248f); cube->textureCoord(0.0f, 1.0f);
	cube->position( 0.5f, -0.5f,  0.0f); cube->normal( 0.666667f, -0.333333f, -0.666667f); cube->textureCoord(1.0f, 1.0f);
	cube->position(-0.5f, -0.5f,  1.0f); cube->normal(-0.666667f, -0.333333f,  0.666667f); cube->textureCoord(0.0f, 0.0f);
	cube->position( 0.5f,  0.5f,  1.0f); cube->normal( 0.666667f,  0.333333f,  0.666667f); cube->textureCoord(1.0f, 0.0f);
	cube->position(-0.5f, -0.5f,  1.0f); cube->normal(-0.666667f, -0.333333f,  0.666667f); cube->textureCoord(0.0f, 1.0f);
	cube->position( 0.5f, -0.5f,  1.0f); cube->normal( 0.408248f, -0.816497f,  0.408248f); cube->textureCoord(1.0f, 1.0f);
	cube->position(-0.5f,  0.5f,  1.0f); cube->normal(-0.408248f,  0.816497f,  0.408248f); cube->textureCoord(0.0f, 0.0f);
	cube->position(-0.5f,  0.5f,  0.0f); cube->normal(-0.666667f,  0.333333f, -0.666667f); cube->textureCoord(0.0f, 1.0f);
	cube->position(-0.5f, -0.5f,  0.0f); cube->normal(-0.408248f, -0.816497f, -0.408248f); cube->textureCoord(1.0f, 1.0f);
	cube->position(-0.5f, -0.5f,  1.0f); cube->normal(-0.666667f, -0.333333f,  0.666667f); cube->textureCoord(1.0f, 0.0f);
	cube->position( 0.5f, -0.5f,  0.0f); cube->normal( 0.666667f, -0.333333f, -0.666667f); cube->textureCoord(0.0f, 1.0f);
	cube->position( 0.5f,  0.5f,  0.0f); cube->normal( 0.408248f,  0.816497f, -0.408248f); cube->textureCoord(1.0f, 1.0f);
	cube->position( 0.5f, -0.5f,  1.0f); cube->normal( 0.408248f, -0.816497f,  0.408248f); cube->textureCoord(0.0f, 0.0f);
	cube->position( 0.5f, -0.5f,  0.0f); cube->normal( 0.666667f, -0.333333f, -0.666667f); cube->textureCoord(1.0f, 0.0f);
	cube->position(-0.5f, -0.5f,  0.0f); cube->normal(-0.408248f, -0.816497f, -0.408248f); cube->textureCoord(0.0f, 0.0f);
	cube->position(-0.5f,  0.5f,  1.0f); cube->normal(-0.408248f,  0.816497f,  0.408248f); cube->textureCoord(1.0f, 0.0f);
	cube->position( 0.5f,  0.5f,  0.0f); cube->normal( 0.408248f,  0.816497f, -0.408248f); cube->textureCoord(0.0f, 1.0f);
	cube->position(-0.5f,  0.5f,  0.0f); cube->normal(-0.666667f,  0.333333f, -0.666667f); cube->textureCoord(1.0f, 1.0f);
	cube->position( 0.5f,  0.5f,  1.0f); cube->normal( 0.666667f,  0.333333f,  0.666667f); cube->textureCoord(0.0f, 0.0f);

	cube->triangle( 0,  1,  2); cube->triangle( 3,  1,  0);
	cube->triangle( 4,  5,  6); cube->triangle( 4,  7,  5);
	cube->triangle( 8,  9, 10); cube->triangle(10,  7,  8);
	cube->triangle( 4, 11, 12); cube->triangle( 4, 13, 11);
	cube->triangle(14,  8, 12); cube->triangle(14, 15,  8);
	cube->triangle(16, 17, 18);	cube->triangle(16, 19, 17);

	cube->end();
	
	return cube;
}

int Projectile::bullets = 0;