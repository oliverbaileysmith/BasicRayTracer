#pragma once

#include "Ray.h"

#include "vendor/glm/gtx/norm.hpp"

class Material;

struct HitRecord {
	glm::dvec3 m_HitPoint;
	glm::dvec3 m_Normal;
	std::shared_ptr<Material> m_MaterialPtr;
	double m_T;
	bool m_FrontFace;

	inline void m_SetFaceNormal(const Ray &ray, const glm::dvec3 &outwardNormal) {
		m_FrontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
		m_Normal = m_FrontFace ? outwardNormal : -outwardNormal;
	}
};

class HittableObject {
public:
	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const = 0;
};