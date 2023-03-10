#pragma once

#include <memory>

#include "Ray.h"
#include "AABB.h"

#include "vendor/glm/gtx/norm.hpp"

class Material;

struct HitRecord {
	glm::dvec3 m_HitPoint;
	glm::dvec3 m_Normal;
	std::shared_ptr<Material> m_MaterialPtr;
	double m_T;
	double m_U;
	double m_V;
	bool m_FrontFace;

	inline void m_SetFaceNormal(const Ray &ray, const glm::dvec3 &outwardNormal) {
		m_FrontFace = glm::dot(ray.GetDirection(), outwardNormal) < 0;
		m_Normal = m_FrontFace ? outwardNormal : -outwardNormal;
	}
};

class HittableObject {
public:
	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const = 0;
	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const = 0;
};