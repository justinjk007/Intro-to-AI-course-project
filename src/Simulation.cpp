#include "Simulation.hpp"

Simulation::Simulation()
{
	// Dont actually know what this is needed for yet...
	window = 0;
	renderer = 0;
}

~Simulation::Simulation()
{

}

bool Simulation::Init()
{
	// Flag
	bool success = true;

	// Initialize SDL
	// SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS)
	// If you want to intialize multiple things
	//(SDL_INIT_EVERYTHING) for an umbrella solution
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			// Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void Simulation::Clean()
{
	// Clean up objects
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	// Might clean up other objects here?
}

void Simulation::Run()
{
	// Main loop location, handle events, update and render here



	// Delete objects, clean up any memory allocations

	Clean();

	SDL_Quit();
}

void Simulation::NewSimulation()
{
	// setup objects here, call constructors etc...

}

void Simulation::Update()
{
	// Simulation logic here


	// Call update functions within Agent/Target

}

void Simulation::Render()
{
	// Initialize renderer color, clear screen to black
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw things in order, so background first, then foreground
	// Anything not drawn to the back buffer will not be rendered

	// Render Agents


	// Render Targets


	// Update screen
	SDL_RenderPresent(renderer);
}

bool loadTextures()
{
	// Flag
	bool success = true;

	// Load up textures for each agent and target here

	return success;
}