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

	virtual bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;

private:
	std::vector<std::shared_ptr<HittableObject>> m_HittableObjects;
};