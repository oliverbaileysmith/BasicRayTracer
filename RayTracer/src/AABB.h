#include "Util.h"
#include "Ray.h"

class AABB {
public:
	AABB();
	AABB(const glm::dvec3 &min, const glm::dvec3 &max);

	bool Hit(const Ray &ray, double tMin, double tMax) const;

	glm::dvec3 m_Minimum;
	glm::dvec3 m_Maximum;
};

AABB buildSurroundingAABB(AABB box0, AABB box1);