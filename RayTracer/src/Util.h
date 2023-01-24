#pragma once

#include <cmath>
#include <limits>
#include <memory>

#include <cstdlib>

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/gtx/norm.hpp"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const float POSITIVE_INFINITY = std::numeric_limits<float>::infinity();
const float PI = 3.1415926535897932385f;

// Utility Functions

inline float degreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

inline float randomFloat() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline float randomFloat(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max - min) * randomFloat();
}

inline glm::vec3 randomVec3() {
    return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}

inline glm::vec3 randomVec3(float min, float max) {
    return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}

inline glm::vec3 randomInUnitSphere() {
    while (true) {
        glm::vec3 p = randomVec3(-1.0f, 1.0f);
        if (glm::length2(p) >= 1)
            continue;
        return p;
    }
}

inline float clamp(float x, float min, float max) {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}