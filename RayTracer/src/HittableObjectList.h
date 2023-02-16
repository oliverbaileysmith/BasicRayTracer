#pragma once

#include "HittableObject.h"

#include <memory>
#include <vector>

class HittableObjectList : public HittableObject {
public:
	HittableObjectList();
	HittableObjectList(std::shared_ptr<HittableObject> hittableObject);

	void clear();
	void add(std::shared_ptr<HittableObject> hittableObject);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;
	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

	std::vector<std::shared_ptr<HittableObject>> m_HittableObjects;
};