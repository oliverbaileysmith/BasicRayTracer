#include "Box.h"

Box::Box() {}

Box::Box(const glm::dvec3 &p0, const glm::dvec3 &p1, std::shared_ptr<Material> material) {
	m_BoxMin = p0;
	m_BoxMax = p1;

	m_Sides.add(std::make_shared<XYRect>(p0.x, p1.x, p0.y, p1.y, p1.z, material));
	m_Sides.add(std::make_shared<XYRect>(p0.x, p1.x, p0.y, p1.y, p0.z, material));
	
	m_Sides.add(std::make_shared<XZRect>(p0.x, p1.x, p0.z, p1.z, p1.y, material));
	m_Sides.add(std::make_shared<XZRect>(p0.x, p1.x, p0.z, p1.z, p0.y, material));
	
	m_Sides.add(std::make_shared<YZRect>(p0.y, p1.y, p0.z, p1.z, p1.x, material));
	m_Sides.add(std::make_shared<YZRect>(p0.y, p1.y, p0.z, p1.z, p0.x, material));
}

bool Box::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	return m_Sides.Hit(ray, tMin, tMax, hitRecord);
}

bool Box::buildAABB(double time0, double time1, AABB &outputAABB) const {
	outputAABB = AABB(m_BoxMin, m_BoxMax);
	return true;
}