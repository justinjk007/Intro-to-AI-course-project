#include "AI.hpp"

void Agent::Update()
{
    // Logic/Calculations happen here

    // Movement algorithm here
}

void Target::Update()
{
    // Logic/Calculations happen here

    // If a target gets picked up, remove it from the environment
    if (this->pickedUp == true) {
        this->location.x = NULL;
        this->location.y = NULL;
    }
}

void Agent::ScanArea()
{
    // Going to look up how to scan area in a radial fashion
}

void Agent::TargetFound()
{
    this->targetsFound++;
}
