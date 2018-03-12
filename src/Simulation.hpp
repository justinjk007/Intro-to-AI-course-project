#ifndef SIMULATION_HPP
#define SIMULATION_HPP

class Simulation 
{
public:
	Simulation();
	~Simulation();

	bool Init();
	void Run();
	bool loadTextures();

private:
	// SDL objects
	SDL_Window * window;
	SDL_Renderer* renderer;

	// Clean up any memory allocations or object declarations
	void Clean();
	// Call internal update functions of objects
	void Update(float delta);
	// Call internal render functions of objects
	void Render(float delta);
	// Run setup for objects after initialization procedures
	void NewSimulation();
};

#endif SIMULATION_HPP