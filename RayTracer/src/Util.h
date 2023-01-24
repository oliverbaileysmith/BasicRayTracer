#pragma once

#include <cmath>
#include <limits>
#include <memory>

#include <cstdlib>

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

inline float random_float() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float random_float(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_float();
}