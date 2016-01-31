#ifndef _LOOP_HANDLER_HPP_
#define _LOOP_HANDLER_HPP_

#include <SDL.h>

class LoopHandler{
public:

	virtual void pre(){}
	virtual void process(SDL_Event* event){}
	virtual void logics(){}
	virtual void render(){}
	virtual void pos(){}

	virtual bool active(){ return true; }

private:
};

#endif