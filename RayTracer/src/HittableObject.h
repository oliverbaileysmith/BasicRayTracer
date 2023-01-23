#pragma once

#include "Ray.h"

struct HitRecord {
	glm::vec3 m_HitPoint;
	glm::vec3 m_SurfaceNormal;
	float m_t;
};

class HittableObject {
public:
	virtual bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const = 0;
};