#include <glad/glad.h>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mouse.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <array>
#include <iostream>
#include <map>

#include "Simulation.h"
#include "World.h"
#include "Input.h"
#include "MasterRenderer.h"


SDL_Window * window;
MasterRenderer * renderer;
Simulation * simulation;
World * world;
Input * input;

const int width = 1920, height = 1080;
const int FPS = 60;
const int TPS = 1000;

void next_frame ()
{
	input->update(renderer->camera);
    renderer->render(world);
	SDL_GL_SwapWindow(window);
}

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Cloth++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_CreateContext(window);
    SDL_WarpMouseInWindow(window, width / 2, height / 2);

    SDL_SetWindowGrab(window, SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    world = new World();
    input = new Input();
    renderer = new MasterRenderer(width, height);
    simulation = new Simulation(world);

    SDL_Event event;
    int running = 1;
    int frame = 0;
    double mspf = 1000./FPS;
    double mspt = 1000./TPS;
    int t_prev = SDL_GetTicks();
    int t_last = t_prev;
    int last_tick = t_prev;

    while(running)
    {
    	int t = SDL_GetTicks();

		if((t-last_tick) > mspt)
		{
            simulation->update(1./1000.);
            last_tick = t;
		}

		if ((t - t_prev) > mspf)
		{
			next_frame();

			t_prev = t;

			if(++frame > FPS)
			{
				frame = 0;
				float cFps = (1000. / (t - t_last)) * FPS;
				t_last = SDL_GetTicks();
				std::cout << "FPS: " << cFps << std::endl;
			}
		}
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    delete renderer;
    delete input;

    return 0;
}
