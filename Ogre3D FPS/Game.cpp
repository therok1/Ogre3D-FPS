#include "Game.h"

Game::Game() : 
	OgreBites::ApplicationContext("FPS Demo"), 
	m_player(nullptr),
	m_cube(nullptr),
	m_cube1(nullptr),
	m_cube2(nullptr),
	m_ground(nullptr)
{
	for (char ch = 'a'; ch <= 'z'; ch++)
	{
		m_keys[ch] = false;
	}

	m_keys[static_cast<char>(32)] = false;

	m_entities.reserve(4);
}

void Game::setup()
{
	OgreBites::ApplicationContext::setup();

	addInputListener(this);

	Ogre::Root* root = getRoot();
	Ogre::SceneManager* scnMgr = root->createSceneManager();

	Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
	shadergen->addSceneManager(scnMgr);
	
	scnMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");
	scnMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	scnMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	Ogre::Light* light = scnMgr->createLight("MainLight");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(1.0f, 1.0f, 1.0f);
	light->setSpecularColour(1.0f, 1.0f, 1.0f);

	Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	lightNode->setDirection(0, -1, 0);
	lightNode->attachObject(light);

	Ogre::Plane ground(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		ground,
		1500, 1500, 20, 20,
		true,
		1, 100, 100,
		Ogre::Vector3::UNIT_Z
	);
	
	Ogre::MeshPtr cubeMesh = createCubeMesh("cube", "Examples/red")->convertToMesh("cube.mesh");
	Ogre::MeshPtr cubeMesh1 = createCubeMesh("cube1", "Examples/blue")->convertToMesh("cube1.mesh");

	m_ground = scnMgr->createEntity("ground");
	m_ground->setMaterialName("Examples/BeachStones");
	m_ground->setCastShadows(false);
	scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(m_ground);

	m_cube = scnMgr->createEntity("cube", "cube.mesh");
	m_cube1 = scnMgr->createEntity("cube1", "cube.mesh");
	m_cube2 = scnMgr->createEntity("cube2", "cube.mesh");

	Ogre::SceneNode* cubeNode = scnMgr->getRootSceneNode()->createChildSceneNode();
	cubeNode->setScale(2, 10, 5);
	cubeNode->setPosition(100, 5, -5);
	cubeNode->attachObject(m_cube);

	Ogre::SceneNode* cubeNode1 = scnMgr->getRootSceneNode()->createChildSceneNode();
	cubeNode1->setScale(2, 10, 5);
	cubeNode1->setPosition(200, 5, -25);
	cubeNode1->attachObject(m_cube1);

	Ogre::SceneNode* cubeNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
	cubeNode2->setScale(2, 10, 5);
	cubeNode2->setPosition(400, 5, -45);
	cubeNode2->attachObject(m_cube2);

	m_entities.push_back(m_ground);
	m_entities.push_back(m_cube);
	m_entities.push_back(m_cube1);
	m_entities.push_back(m_cube2);
	
	m_player = std::make_unique<Player>();
	m_player->init(scnMgr);

	getRenderWindow()->addViewport(m_player->getCam());

	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void Game::update(float dt)
{
	m_player->update(dt, m_keys, m_entities);
}

bool Game::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	if (m_keys.find(static_cast<char>(evt.keysym.sym)) != m_keys.end())
	{
		m_keys[static_cast<char>(evt.keysym.sym)] = true;
	}
	
	if (evt.keysym.sym == OgreBites::SDLK_ESCAPE)
	{
		getRoot()->queueEndRendering();
	}
	
	return true;
}

bool Game::keyReleased(const OgreBites::KeyboardEvent& evt)
{
	if (m_keys.find(static_cast<char>(evt.keysym.sym)) != m_keys.end())
	{
		m_keys[static_cast<char>(evt.keysym.sym)] = false;
	}

	return true;
}

bool Game::mouseMoved(const OgreBites::MouseMotionEvent& evt)
{
	m_player->mouseMoved(evt);

	return true;
}

Ogre::ManualObject* Game::createCubeMesh(const std::string& name, const std::string& matName)
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