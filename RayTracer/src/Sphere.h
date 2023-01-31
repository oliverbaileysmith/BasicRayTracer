#pragma once

#include <memory>

#include "HittableObject.h"

class Sphere : public HittableObject {
public:
	Sphere(glm::dvec3 center, double radius, std::shared_ptr<Material> material);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

private:
	glm::dvec3 m_Center;
	double m_Radius;
	std::shared_ptr<Material> m_Material;
};