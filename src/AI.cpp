#include "AI.hpp"
#include <string>

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
        // this->location.x = 0.0;
        // this->location.y = 0.0;
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
