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
		FPSCounter() {}

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
		float accumulatedTime = 0.0f;
		float deltaTime = 0.0f;
		int fps = 0;
		int fpsCounter = 0;
		milliseconds  lastTime;
	};
}

#endif