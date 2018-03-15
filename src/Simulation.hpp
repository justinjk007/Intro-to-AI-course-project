#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Point.hpp"

// Texture wrapper class
class LTexture
{
public:
    LTexture();                           // Initializes variables (constructor)
    ~LTexture();                          // Deallocates memory (destructor)
	SDL_Texture * create_texture_from_surface(SDL_Renderer * sdlRenderer, SDL_Surface * surf, int format, SDL_Color * sdlColorKey, bool destroySurface);
	// Loads image at specified path
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
    // Gets image dimensions
    int getWidth();
    int getHeight();

	SDL_Texture* mTexture;  // The actual hardware texture

private:
    // Image dimensions
    int mWidth;
    int mHeight;
};

class Simulation
{
   public:
    Simulation();
    ~Simulation();
    bool Init();
    bool loadTextures();

	// SDL objects
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;

private:
    // Screen dimension constants
    const int kScreenWidth  = 1000;  // 640
    const int kScreenHeight = 1000;  // 480

    void Render(Point<int> newLoc, int agentID);  // Render object to screen
    void NewSimulation();  // Run setup for objects after initialization procedures
};

#endif
