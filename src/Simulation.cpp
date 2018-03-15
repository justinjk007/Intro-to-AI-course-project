#include "Simulation.hpp"

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
    // Free texture if it exists
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth   = 0;
        mHeight  = 0;
    }
}

// Code courtesy of FluffyDragon#0567 and theweirdnate#6818 from discord
// This formats the texture in a 'better' way.
SDL_Texture* LTexture::create_texture_from_surface(SDL_Renderer* sdlRenderer, SDL_Surface* surf,
                                                   int format, SDL_Color* sdlColorKey,
                                                   bool destroySurface)
{
    if (surf == NULL || sdlRenderer == NULL) {
        return NULL;
    }
    int pixelbytes = 0;
    Uint8 r, g, b, a;
    SDL_Surface* cast_img = SDL_ConvertSurfaceFormat(surf, format, 0);
    pixelbytes            = cast_img->w * cast_img->h;
    pixelbytes            = pixelbytes * 4;
    unsigned char* pixels = (unsigned char*)cast_img->pixels;
    if (sdlColorKey != NULL) {
        for (int i = 0; i < pixelbytes; i++) {
            a = pixels[i + 0];
            r = pixels[i + 1];
            g = pixels[i + 2];
            b = pixels[i + 3];
            if (r == sdlColorKey->r && g == sdlColorKey->g && b == sdlColorKey->b) {
                pixels[i + 0] = 0;
            }
        }
    }
    SDL_Rect rect = {0, 0, cast_img->w, cast_img->h};
    SDL_Texture* newTexture =
        SDL_CreateTexture(sdlRenderer, format, SDL_TEXTUREACCESS_STATIC, cast_img->w, cast_img->h);
    SDL_UpdateTexture(newTexture, &rect, cast_img->pixels, cast_img->w * 4);
    SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(cast_img);
    if (destroySurface) {
        SDL_FreeSurface(surf);
    }
    return newTexture;
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    // Get rid of any preexisting texure
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth   = 0;
        mHeight  = 0;
    }

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
        int format = SDL_PIXELFORMAT_RGBA8888;
        newTexture = create_texture_from_surface(gRenderer, loadedSurface, format, NULL, false);
        // newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
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
    gWindow   = NULL;
    gRenderer = NULL;

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
    Point<int> testPoint(3, 4);
    int ID = 10;
    Render(testPoint, ID);
}

void Simulation::Render(Point<int> newLoc, int agentID)
{
    // Initialize renderer color, clear screen to white
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    // Draw things in order, so background first, then foreground
    // Anything not drawn to the back buffer will not be rendered
    // when RenderPresent is called to be written to the front buffer (screen)

    // Render Agents
    // SDL_Rect controls how large the image is and where it is rendered
    SDL_Rect agentSize;
    agentSize.x = 600;
    agentSize.y = 600;
    agentSize.w = AgentTexture.getWidth();
    agentSize.h = AgentTexture.getHeight();
    SDL_RenderCopy(gRenderer, AgentTexture.mTexture, 0, &agentSize);

    // Render Targets
    // SDL_Rect controls how large the image is and where it is rendered
    SDL_Rect targetSize;
    targetSize.x = 200;
    targetSize.y = 200;
    targetSize.w = TargetA1Texture.getWidth();
    targetSize.h = TargetA1Texture.getHeight();
    SDL_RenderCopy(gRenderer, TargetA1Texture.mTexture, 0, &targetSize);

    SDL_Rect targetSize2;
    targetSize2.x = 600;
    targetSize2.y = 595;
    targetSize2.w = TargetA2Texture.getWidth();
    targetSize2.h = TargetA2Texture.getHeight();
    SDL_RenderCopy(gRenderer, TargetA2Texture.mTexture, 0, &targetSize2);

    // Update screen
    SDL_RenderPresent(gRenderer);
}

bool Simulation::loadTextures()
{
    // Flag
    bool success = true;

    // Load agent texture
    if (!AgentTexture.loadFromFile("assets/agentAv2-100x100.png", gRenderer)) {
        printf("Failed to load Agent texture image!\n");
        success = false;
    }

    // Load target (A1) texture
    if (!TargetA1Texture.loadFromFile("assets/targetA1-10x10.png", gRenderer)) {
        printf("Failed to load Target A1 texture image!\n");
        success = false;
    }

    // Load target (A2) texture
    if (!TargetA2Texture.loadFromFile("assets/targetA2-10x10.png", gRenderer)) {
        printf("Failed to load Target A2 texture image!\n");
        success = false;
    }

    return success;
}
