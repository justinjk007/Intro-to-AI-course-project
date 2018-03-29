#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <QObject>
#include <string>
#include "Point.hpp"
#undef main

// Texture wrapper class
class LTexture
{
   public:
    LTexture();   // Initializes variables (constructor)
    ~LTexture();  // Deallocates memory (destructor)
    SDL_Texture* create_texture_from_surface(SDL_Renderer* sdlRenderer, SDL_Surface* surf,
                                             int format, SDL_Color* sdlColorKey,
                                             bool destroySurface);
    bool loadFromFile(std::string path, SDL_Renderer* gRenderer);  // Loads image at specified path
    // Gets image dimensions
    int getWidth();
    int getHeight();

    SDL_Texture* mTexture;  // The actual hardware texture

   private:
    // Image dimensions
    int mWidth;
    int mHeight;
};

class Simulation : public QObject
{
    Q_OBJECT
public:
    Simulation();
    ~Simulation();
    void renderAgent(Point<int>, int);   // update/render agent
    void renderTarget(Point<int>, int);  // ipdate/render target

private:
    // Screen dimension constants
    const int kScreenWidth  = 1000;  // 640
    const int kScreenHeight = 1000;  // 480
    // SDL objects
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    bool Init();
    bool loadTextures();
    LTexture AgentTexture[5];   // Array containing 5 images for 5 Agents
    LTexture TargetTexture[5];  // Array containing 5 images for 5 Targets
};

#endif
