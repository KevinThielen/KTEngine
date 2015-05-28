#ifndef KTE_FPS_COUNTER_H
#define KTE_FPS_COUNTER_H

#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace kte
{
	class FPSCounter
	{
	public:
		FPSCounter() 
		{
		    accumulatedTime = 0.0f;
		    deltaTime = 0.0f;
		    fps = 0;
		    fpsCounter = 0;
		    lastTime = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
		}

		void update()
		{
			milliseconds currentMs = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
			deltaTime = (currentMs - lastTime).count() / 1000.0f;
			lastTime = currentMs;

			accumulatedTime += deltaTime;
			fpsCounter++;
			if (accumulatedTime >= 1.0f)
			{
				accumulatedTime = 0.0f;
				fps = fpsCounter;
				fpsCounter = 0;

				std::cout << "FPS: " << fps << std::endl;
			}
		}

		float getFramesPerSecond() { return fps; }
		double getDeltaTime() { return deltaTime; }
	private:
		float accumulatedTime;
		float deltaTime;
		int fps;
		int fpsCounter;
		milliseconds  lastTime;
	};
}

#endif