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

AABB buildSurroundingAABB(AABB box0, AABB box1) {
	glm::dvec3 min(
		std::fmin(box0.m_Minimum.x, box0.m_Minimum.x),
		std::fmin(box0.m_Minimum.y, box0.m_Minimum.y),
		std::fmin(box0.m_Minimum.z, box0.m_Minimum.z)
	);

	glm::dvec3 max(
		std::fmax(box0.m_Maximum.x, box0.m_Maximum.x),
		std::fmax(box0.m_Maximum.y, box0.m_Maximum.y),
		std::fmax(box0.m_Maximum.z, box0.m_Maximum.z)
	);

	return AABB(min, max);
}