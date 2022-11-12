#include <Ogre.h>
#include <OgreApplicationContext.h>

#include "Game.h"
#include "Time.h"

int main(int argc, char* argv[])
{
	float dt;

	Time time;
	Game game;
	game.initApp();
	game.getRoot()->clearEventTimes();

	while (!game.getRoot()->endRenderingQueued())
	{
		dt = static_cast<float>(time.computeDeltaTime()) / 1000.0f;

		if (!game.getRoot()->renderOneFrame())
		{
			break;
		}

		game.update(dt);
		time.delayTime();
	}
	
	game.closeApp();
	
	return 0;
}
