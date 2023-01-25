#pragma once

#include "HittableObject.h"

class Sphere : public HittableObject {
public:
	Sphere(glm::dvec3 center, double radius);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

private:
	glm::dvec3 m_Center;
	double m_Radius;
};