#pragma once

#include <cmath>
#include <limits>
#include <memory>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
const float PI = 3.1415926535897932385f;

// Utility Functions

inline float degrees_to_radians(float degrees) {
    return degrees * PI / 180.0f;
}