#include "Ray.h"

Ray::Ray(const glm::vec3 &origin, const glm::vec3 &direction)
	: m_Origin(origin), m_Direction(direction)
{

}

Ray::~Ray() {}

glm::vec3 Ray::GetOrigin() const {
	return m_Origin;
}

glm::vec3 Ray::GetDirection() const {
	return m_Direction;
}

glm::vec3 Ray::CalculateAtDistance(float t) const {
	return m_Origin + t * m_Direction;
}