#pragma once

#include "HittableObject.h"

class Sphere : public HittableObject {
public:
	Sphere(glm::vec3 center, float radius);

	virtual bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;

private:
	glm::vec3 m_Center;
	float m_Radius;
};