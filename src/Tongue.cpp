#include "Tongue.hpp"

bool tongueUp = false;

// Toggles the tongue state, whatever it is
void toggleTongue()
{
    tongueUp = !tongueUp;
    Tongue.set_state(!tongueUp);
}

// If this is called with true, then invert it and use it for the tongue actuator
void toggleTongue(bool up)
{
    tongueUp = up;
    Tongue.set_state(!tongueUp);
}

// Gets the state of the tongue (true = up, false = down)
bool getState()
{
    return tongueUp;
}

