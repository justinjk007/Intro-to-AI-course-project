#include "Simulation.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "Point.hpp"

// Scene textures
LTexture AgentTexture;
LTexture TargetA1Texture;
LTexture TargetA2Texture;

LTexture::LTexture()
{
	// Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// Free texture if it exists
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool LTexture::loadFromFile(std::string path)
{
	// Get rid of any preexisting texure
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	// Final texture
	SDL_Texture* newTexture = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		// Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
				SDL_GetError());
		}
		else {
			// Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	// Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Simulation::Simulation()
{
    // Dont actually know what this is needed for yet...
    //gWindow   = 0;
    //gRenderer = 0;

    Init();
    loadTextures();
    NewSimulation();
}

Simulation::~Simulation()
{
    // Clean up objects
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
	IMG_Quit();
    SDL_Quit();
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
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
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

void Simulation::NewSimulation()
{
    // setup objects here, call constructors etc...
}

void Simulation::Render(Point<int> newLoc, int agentID)
{
    // Initialize renderer color, clear screen to white
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Draw things in order, so background first, then foreground
    // Anything not drawn to the back buffer will not be rendered
	//when RenderPresent is called to be written to the front buffer (screen)

    // Render Agents
    // SDL_Rect controls how large the image is and where it is rendered
    SDL_Rect agentSize;
    agentSize.x = 600;
    agentSize.y = 600;
    agentSize.w = AgentTexture.getWidth();
    agentSize.h = AgentTexture.getHeight();
    SDL_RenderCopy(gRenderer, AgentTexture, 0, &agentSize);

    // Render Targets
    // SDL_Rect controls how large the image is and where it is rendered
    SDL_Rect targetSize;
    targetSize.x = 200;
    targetSize.y = 200;
    targetSize.w = TargetA1Texture.getWidth();
	targetSize.h = TargetA1Texture.getHeight();
    SDL_RenderCopy(gRenderer, TargetA1Texture, 0, &targetSize);

	SDL_Rect targetSize2;
	targetSize2.x = 600;
	targetSize2.y = 200;
	targetSize2.w = TargetA2Texture.getWidth();
	targetSize2.h = TargetA2Texture.getHeight();
	SDL_RenderCopy(gRenderer, TargetA2Texture, 0, &targetSize2);

    // Update screen
    SDL_RenderPresent(gRenderer);
}

bool loadTextures()
{
    // Flag
    bool success = true;

	// Load agent texture
	if (!AgentTexture.loadFromFile("assets/agentAv2-100x100.png")) {
		printf("Failed to load Agent texture image!\n");
		success = false;
	}

	// Load target (A1) texture
	if (!TargetA1Texture.loadFromFile("assets/targetA1-10x10.png")) {
		printf("Failed to load Target A1 texture image!\n");
		success = false;
	}

	// Load target (A2) texture
	if (!TargetA2Texture.loadFromFile("assets/targetA2-10x10.png")) {
		printf("Failed to load Target A2 texture image!\n");
		success = false;
	}

    return success;
}
