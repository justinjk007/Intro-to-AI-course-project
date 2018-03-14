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
    bool loadFromFile(std::string path);  // Loads image at specified path
    // Gets image dimensions
    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;  // The actual hardware texture
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
    void Run();
    bool loadTextures();

private:
    // Screen dimension constants
    const int kScreenWidth  = 1000;  // 640
    const int kScreenHeight = 1000;  // 480
    // SDL objects
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    void Render(Point<int> newLoc, int agentID);  // Render object to screen
    void NewSimulation();  // Run setup for objects after initialization procedures
};

#endif SIMULATION_HPP
