#pragma once

#include "vendor/glm/ext/vector_double3.hpp"

class Ray {
public:
	Ray(const glm::dvec3 &origin, const glm::dvec3 &direction);
	~Ray();

	glm::dvec3 GetOrigin() const;
	glm::dvec3 GetDirection() const;

	glm::dvec3 GetPositionAtDistance(double t) const;

private:
	glm::dvec3 m_Origin;
	glm::dvec3 m_Direction;
};