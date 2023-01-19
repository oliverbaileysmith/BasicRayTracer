#pragma once

#include "vendor/glm/ext/vector_float3.hpp"

class Ray {
public:
	Ray(const glm::vec3 &origin, const glm::vec3 &direction);
	~Ray();

	glm::vec3 GetOrigin() const;
	glm::vec3 GetDirection() const;

	glm::vec3 GetPositionAtDistance(float t) const;

private:
	glm::vec3 m_Origin;
	glm::vec3 m_Direction;
};