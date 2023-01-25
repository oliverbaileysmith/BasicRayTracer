#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &direction)
	: m_Origin(origin), m_Direction(direction)
{

}

Ray::~Ray() {}

glm::dvec3 Ray::GetOrigin() const {
	return m_Origin;
}

glm::dvec3 Ray::GetDirection() const {
	return m_Direction;
}

glm::dvec3 Ray::GetPositionAtDistance(double t) const {
	return m_Origin + t * m_Direction;
}