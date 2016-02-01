#ifndef _LOOP_HANDLER_HPP_
#define _LOOP_HANDLER_HPP_

#include <SDL.h>

class LoopHandler{
public:

	virtual void pre() = 0;
	virtual void process(SDL_Event* event) = 0;
	virtual void logics() = 0;
	virtual void render() = 0;
	virtual void pos() = 0;

	virtual bool active(){ return true; }

private:
};

#endif