#pragma once

#include "HittableObject.h"

class Translate : public HittableObject {
public:
	Translate(std::shared_ptr<HittableObject> obj, const glm::dvec3 &offset);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;
	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

public:
	std::shared_ptr<HittableObject> m_Obj;
	glm::dvec3 m_Offset;
};