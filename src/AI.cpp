#include "AI.hpp"


void Agent::SetAgentLocation(Point<int> loc)
{
	this->location.x = loc.x;
	this->location.y = loc.y;
}

void Target::SetTargetLocation(Point<int> loc)
{
	this->location.x = loc.x;
	this->location.y = loc.y;
}

void Agent::Update()
{
	// Logic/Calculations happen here

	// Movement algorithm here

}

void Target::Update()
{
	// Logic/Calculations happen here

	// If a target gets picked up, remove it from the environment
	if (this->pickedUp == true)
	{
		this->location.x = NULL;
		this->location.y = NULL;
	}

}

void Agent::Render()
{
	// Render Agent
	// SDL_Rect controls how large the image is
	SDL_Rect agentSize;
	agentSize.x = 0;
	agentSize.y = 0;
	agentSize.w = 800;
	agentSize.h = 21;
	//SDL_RenderCopy(renderer, putTextureHere, 0, &dstrect);
}

void Target::Render()
{
	// Render Target
	// SDL_Rect controls how large the image is
	SDL_Rect targetSize;
	targetSize.x = 0;
	targetSize.y = 0;
	targetSize.w = 800;
	targetSize.h = 21;
	//SDL_RenderCopy(renderer, putTextureHere, 0, &dstrect);
}

void Agent::ScanArea()
{
	// Going to look up how to scan area in a radial fashion

}

void Agent::TargetFound()
{
	this->targetsFound++;
}