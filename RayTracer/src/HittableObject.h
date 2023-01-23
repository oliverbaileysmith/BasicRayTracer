#pragma once

#include "Ray.h"

#include "vendor/glm/gtx/norm.hpp"

struct HitRecord {
	glm::vec3 m_HitPoint;
	glm::vec3 m_Normal;
	float m_T;
	bool m_FrontFace;

	inline void m_SetFaceNormal(const Ray &ray, const glm::vec3 &outwardNormal) {
		m_FrontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
		m_Normal = m_FrontFace ? outwardNormal : -outwardNormal;
	}
};

class HittableObject {
public:
	virtual bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const = 0;
};