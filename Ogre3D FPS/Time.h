#pragma once

#include <SDL.h>

#include <algorithm>

class Time
{
public:

	Time();

	unsigned int computeDeltaTime();

	void delayTime();

	static double getTimeSinceStart() { return timeSinceStart; }

private:

	const static int FPS = 144;
	const static int FRAME_DELAY = 1000 / FPS;
	const unsigned int MAX_DT = 50;

	unsigned int m_frameStart;

	unsigned int m_lastFrame;

	unsigned int m_frameTime;

	static double timeSinceStart;

};
