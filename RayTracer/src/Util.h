#pragma once

#include <cmath>
#include <limits>
#include <memory>

#include <cstdlib>

#include "vendor/glm/ext/vector_double3.hpp"
#include "vendor/glm/gtx/norm.hpp"

// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// Utility Functions

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

inline double randomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * randomDouble();
}

inline glm::dvec3 randomVec3() {
    return glm::dvec3(randomDouble(), randomDouble(), randomDouble());
}

inline glm::dvec3 randomVec3(double min, double max) {
    return glm::dvec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

inline glm::dvec3 randomInUnitSphere() {
    while (true) {
        glm::dvec3 p = randomVec3(-1.0, 1.0);
        if (glm::length2(p) >= 1)
            continue;
        return p;
    }
}

inline glm::dvec3 randomUnitVector() {
    return glm::normalize(randomInUnitSphere());
}

inline glm::dvec3 randomInHemisphere(const glm::dvec3 &normal) {
    glm::dvec3 inUnitSphere = randomInUnitSphere();
    if (glm::dot(inUnitSphere, normal) > 0.0)
        return inUnitSphere;
    else
        return -inUnitSphere;
}

inline bool nearZero(glm::dvec3 dvec3) {
    const double s = 1e-8;
    return (std::fabs(dvec3.x) < s) && (std::fabs(dvec3.y) < s) && (std::fabs(dvec3.z) < s);
}

inline double clamp(double x, double min, double max) {
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}