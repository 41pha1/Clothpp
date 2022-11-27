#include "Input.h"

#include <glm/detail/type_vec3.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/trigonometric.hpp>
#include <SDL_keycode.h>
#include <SDL.h>
#include <SDL_main.h>
#include <SDL_mouse.h>
#include <cmath>

#include "Camera.h"
#include "Simulation.h"
#include <iostream>

Input::Input()
{
	mouse = new Mouse();
}

void Input::pollInputs() 
{
	SDL_Event event;
	bool Mousefirst = true;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			keyboard[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			keyboard[event.key.keysym.sym] = false;
			break;
		case SDL_MOUSEMOTION:
			if (!Mousefirst)
			{
				mouse->dx = event.motion.xrel;
				mouse->dy = event.motion.yrel;
			}
			else {
				Mousefirst = false;
				mouse->dx = 0;
				mouse->dy = 0;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse->left = (event.button.button == SDL_BUTTON_LEFT);
			mouse->right = (event.button.button == SDL_BUTTON_RIGHT);
			break;
		case SDL_QUIT:

			break;
		}
	}
}

void Input::update(Camera * cam)
{
	pollInputs();

	if(keyboard[SDLK_l])
	{
		cam->renderWireframe = !cam->renderWireframe;
		keyboard[SDLK_l] = false;
	}

	float sin = std::sin(glm::radians(cam->yaw));
	float cos = std::cos(glm::radians(cam->yaw));

	glm::vec3 movement = glm::vec3(0,0,0);
	if(keyboard[SDLK_s])
		movement += glm::vec3(-1, 0, 0) * cos + glm::vec3(0, 0, -1) * sin;

	if(keyboard[SDLK_w])
		movement += glm::vec3(1, 0, 0) * cos + glm::vec3(0, 0, 1) * sin;

	if(keyboard[SDLK_d])
		movement += glm::vec3(0, 0, 1) * cos + glm::vec3(-1, 0, 0) * sin;

	if(keyboard[SDLK_a])
		movement += glm::vec3(0, 0, -1) * cos + glm::vec3(1, 0, 0) * sin;

	if(keyboard[SDLK_SPACE])
		movement.y += 1;

	if(keyboard[SDLK_LSHIFT])
		movement.y -= 1;

	else if(keyboard[SDLK_LCTRL])
	{
		movement *= 1.5;
	}

	cam->accelerate(movement * cam->SPEED);

	cam->pitch -= (mouse->dy) * 1.;
	cam->yaw += (mouse->dx) * 1.;

	mouse->dy = 0;
	mouse->dx = 0;

	if(cam->pitch > 89)
		cam->pitch = 89;

	if(cam->pitch < -89)
		cam->pitch = -89;
}

Input::~Input()
{

}

