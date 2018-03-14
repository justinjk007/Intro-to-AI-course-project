#ifndef SIMULATION_HPP
#define SIMULATION_HPP

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

	// Gets image dimensions
	int getWidth();
	int getHeight();

private:
	// The actual hardware texture
	SDL_Texture * mTexture;

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
	const int kScreenWidth = 1000;  // 640
	const int kScreenHeight = 1000;  // 480
	// SDL objects
	SDL_Window * gWindow;
	SDL_Renderer* gRenderer;

	// Render object to screen
	void Render(Point<int> newLoc, int agentID);
	// Run setup for objects after initialization procedures
	void NewSimulation();
};

#endif SIMULATION_HPP