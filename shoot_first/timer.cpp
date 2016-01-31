#include "timer.hpp"

void Timer::start(){
	if (running)
		stop();

	running = true;
	counter = SDL_GetTicks();
}

void Timer::pause(){
	if (!running)
		return;

	paused = true;
	pcounter = SDL_GetTicks();
}

void Timer::unpause(){
	if (!paused)
		return;

	paused = false;
	counter += SDL_GetTicks() - pcounter;
	pcounter = 0;
}

void Timer::stop(){
	if (!running)
		return;

	paused = false;
	running = false;
	counter = 0;
	pcounter = 0;
}

bool Timer::compare(unsigned int ms){
	unsigned int now = SDL_GetTicks();
	if (now - counter >= ms){
		counter = now;
		return true;
	}

	return false;
}