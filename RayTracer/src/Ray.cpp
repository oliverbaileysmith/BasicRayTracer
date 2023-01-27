#include "Ray.h"

Ray::Ray() {}

Ray::Ray(const glm::dvec3 &origin, const glm::dvec3 &direction, double time)
	: m_Origin(origin), m_Direction(direction), m_Time(time)
{

}

Ray::~Ray() {}

glm::dvec3 Ray::GetOrigin() const {
	return m_Origin;
}

glm::dvec3 Ray::GetDirection() const {
	return m_Direction;
}

double Ray::GetTime() const {
	return m_Time;
}

glm::dvec3 Ray::GetPositionAtDistance(double t) const {
	return m_Origin + t * m_Direction;
}