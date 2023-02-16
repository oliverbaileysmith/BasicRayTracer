#pragma once

#include "Util.h"
#include "AARect.h"
#include "HittableObject.h"
#include "HittableObjectList.h"

class Box : public HittableObject {
public:
	Box();
	Box(const glm::dvec3 &p0, const glm::dvec3 &p1, std::shared_ptr<Material> material);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;
	virtual bool buildAABB(double time0, double tim1, AABB &outputAABB) const override;

	glm::dvec3 m_BoxMin;
	glm::dvec3 m_BoxMax;
	HittableObjectList m_Sides;
};