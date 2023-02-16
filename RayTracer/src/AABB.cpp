#include "AABB.h"

AABB::AABB() {}

AABB::AABB(const glm::dvec3 &min, const glm::dvec3 &max)
	: m_Minimum(min), m_Maximum(max)
{}

bool AABB::Hit(const Ray &ray, double tMin, double tMax) const {
	for (int i = 0; i < 3; i++) {

		double t0 = std::fmin(
			(m_Minimum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i],
			(m_Maximum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i]
		);

		double t1 = std::fmax(
			(m_Minimum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i],
			(m_Maximum[i] - ray.GetOrigin()[i]) / ray.GetDirection()[i]
		);

		tMin = std::fmax(t0, tMin);
		tMax = std::fmax(t1, tMax);

		if (tMax <= tMin)
			return false;
	}
	return true;
}

AABB buildSurroundingAABB(AABB aabb0, AABB aabb1) {
	glm::dvec3 min(
		std::fmin(aabb0.m_Minimum.x, aabb1.m_Minimum.x),
		std::fmin(aabb0.m_Minimum.y, aabb1.m_Minimum.y),
		std::fmin(aabb0.m_Minimum.z, aabb1.m_Minimum.z)
	);

	glm::dvec3 max(
		std::fmax(aabb0.m_Maximum.x, aabb1.m_Maximum.x),
		std::fmax(aabb0.m_Maximum.y, aabb1.m_Maximum.y),
		std::fmax(aabb0.m_Maximum.z, aabb1.m_Maximum.z)
	);

	return AABB(min, max);
}