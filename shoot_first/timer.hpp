#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <SDL.h>

class Timer{
public:
	Timer(){
		paused = false;
		running = false;
	}

	void start();
	void pause();
	void unpause();
	void stop();

	/*return how many miliseconds has passed since the last call to compare(ms)*/
	unsigned int getTicks()const{ if (paused) return SDL_GetTicks() - counter; else return SDL_GetTicks() - pcounter; }

	/*test if the ms miliseconds has passed since the last call to this method*/
	bool compare(unsigned int ms);

	bool isPaused()const{
		return paused;
	}

	bool isRunning()const{
		return running;
	}
private:
	bool paused, running;
	unsigned int counter, pcounter;
};

#endif