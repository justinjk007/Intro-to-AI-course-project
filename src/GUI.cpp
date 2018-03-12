#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "AI.hpp"

// Screen dimension constants
const int kScreenWidth  = 1000;  // 640
const int kScreenHeight = 1000;  // 480

// Texture wrapper class
class LTexture
{
   public:
    // Initializes variables (constructor)
    LTexture();

    // Deallocates memory (destructor)
    ~LTexture();

    // Loads image at specified path
    bool loadFromFile(std::string path);

    // Deallocates texture
    void free();

    // Renders texture at given point
    void render(int x, int y);

    // Gets image dimensions
    int getWidth();
    int getHeight();

   private:
    // The actual hardware texture
    SDL_Texture* mTexture;

    // Image dimensions
    int mWidth;
    int mHeight;
};

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// Window we'll be rendering to
SDL_Window* gWindow = NULL;

// Window renderer
SDL_Renderer* gRenderer = NULL;

// Scene textures
LTexture AgentTexture;
LTexture TargetA1Texture;
LTexture TargetA2Texture;

LTexture::LTexture()
{
    // Initialize
    mTexture = NULL;
    mWidth   = 0;
    mHeight  = 0;
}

LTexture::~LTexture()
{
    // Deallocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    // Get rid of any preexisting texure
    free();

    // Final texture
    SDL_Texture* newTexture = NULL;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        // Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
                   SDL_GetError());
        } else {
            // Get image dimensions
            mWidth  = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    // Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    // Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth   = 0;
        mHeight  = 0;
    }
}

void LTexture::render(int x, int y)
{
    // Set rednering space and render to screen
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool init()
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
    } else 
	{
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

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
		// Should initialize agents/targets list here.

    }

    return success;
}

bool loadMedia()
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

void close()
{
    // Free loaded images
    AgentTexture.free();
    TargetA1Texture.free();
    TargetA2Texture.free();

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow   = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

// This macro disables the extra cmd window popup when in Microsoft windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char* args[])
{
    // Start up SDL and create a window
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        // Load media
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            // main loop or game loop
            while (!quit) {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0) {
                    // User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }

                // Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                // Render background texture to screen
                // gBackgroundTexture.render(0, 0);
				//AgentTexture.render(allAgents[1].location.x, allAgents[1].location.y);

                // Render textures to the screen
                AgentTexture.render(240, 190);

                TargetA1Texture.render(400, 400);

                TargetA2Texture.render(800, 800);

                // Update Screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}
