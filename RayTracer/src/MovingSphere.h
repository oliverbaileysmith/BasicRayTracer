#pragma once

#include "Util.h"
#include "HittableObject.h"

class MovingSphere : public HittableObject {
public:
	MovingSphere();
	MovingSphere(glm::dvec3 center0, glm::dvec3 center1, double time0, double time1, double radius, std::shared_ptr<Material> material);
	~MovingSphere();

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

	glm::dvec3 getCenter(double time) const;

private:
	glm::dvec3 m_Center0;
	glm::dvec3 m_Center1;
	double m_Time0;
	double m_Time1;
	double m_Radius;
	std::shared_ptr<Material> m_Material;

};
