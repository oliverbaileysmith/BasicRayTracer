#pragma once

#include "HittableObject.h"

class RotateY : public HittableObject {
public:
	RotateY(std::shared_ptr<HittableObject> obj, double angle);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;

	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

public:
	std::shared_ptr<HittableObject> m_Obj;
	double m_SinTheta;
	double m_CosTheta;
	bool m_HasAABB;
	AABB m_AABB;
};