#include <SDL.h>

#include <iostream>
#include <stdexcept>
#include <string>

#include "game.hpp"

SDL_Window* initSDL(const std::string& title, unsigned int w, unsigned int h);
SDL_GLContext initOpenGL(SDL_Window* window);
void events(LoopHandler* lhandler);
void logics(LoopHandler* lhandler);
void render(LoopHandler* lhandler);

int main(int argc, char* argv[]){
	//fps counter
	unsigned int fps_c = 0;
	Timer fps_ct;

	const unsigned int DISERED_DELAY = 25;
	unsigned int start, end, loop_t = 0, excess = 0;

	SDL_Event event;
	LoopHandler* handler = nullptr;
	SDL_Window* window = nullptr;
	SDL_GLContext glc = nullptr;

	try{
		window = initSDL("Hardcore!", 500, 500);
		glc= initOpenGL(window);

		handler = new Game();

		handler->pre();
		fps_ct.start();
		while (handler->active()){
			start = SDL_GetTicks();

			while (SDL_PollEvent(&event)){
				handler->process(&event);
			}

			while (excess < DISERED_DELAY){
				handler->logics();
				excess -= DISERED_DELAY;
			}

			handler->logics();

			glClear(GL_COLOR_BUFFER_BIT);
			handler->render();
			SDL_GL_SwapWindow(window);
			
			end = SDL_GetTicks();
			loop_t = end - start;
			if (loop_t < DISERED_DELAY){
				SDL_Delay(DISERED_DELAY - loop_t);
			}
			else{
				excess += DISERED_DELAY - loop_t;
			}

			if (fps_ct.compare(1000)){
				system("cls");
				std::cout << "fps: " << fps_c << std::endl;
				fps_c = 0;
			}

			fps_c++;
		}
		handler->pos();
	}
	catch (std::exception& ex){
		SDL_ShowSimpleMessageBox(::SDL_MessageBoxFlags::SDL_MESSAGEBOX_ERROR, "Error", ex.what(), window);
	}

	delete handler;
	SDL_GL_DeleteContext(glc);
	SDL_DestroyWindow(window);

	return 0;
}

SDL_Window* initSDL(const std::string& title, unsigned int w, unsigned int h){
	SDL_Window* window;

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw std::runtime_error(SDL_GetError());

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (window == NULL)
		throw std::runtime_error(SDL_GetError());

	return window;
}

SDL_GLContext initOpenGL(SDL_Window* window){
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(1.0, 0.0, 0.0, 1.0);

	return SDL_GL_CreateContext(window);
}