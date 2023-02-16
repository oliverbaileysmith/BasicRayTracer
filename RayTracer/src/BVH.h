#pragma once

#include "Util.h"

#include "HittableObjectList.h"

#include <iostream>

class BVHNode : public HittableObject {
public:
	BVHNode();
	BVHNode(const HittableObjectList &list, double time0, double time1);
	BVHNode(const std::vector<std::shared_ptr<HittableObject>> &sourceObjects, size_t start, size_t end, double time0, double time1);

	virtual bool Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const override;
	virtual bool buildAABB(double time0, double time1, AABB &outputAABB) const override;

	std::shared_ptr<HittableObject> m_Left;
	std::shared_ptr<HittableObject> m_Right;
	AABB m_AABB;
};

inline bool boxCompare(const shared_ptr<HittableObject> a, const shared_ptr<HittableObject> b, int axis) {
	AABB boxA;
	AABB boxB;

	if (!a->buildAABB(0, 0, boxA) || !b->buildAABB(0, 0, boxB))
		std::cout << "No bounding box in BVHNode constructor." << std::endl;

	return boxA.m_Minimum[axis] < boxB.m_Minimum[axis];
}


inline bool boxXCompare(const shared_ptr<HittableObject> a, const shared_ptr<HittableObject> b) {
	return boxCompare(a, b, 0);
}

inline bool boxYCompare(const shared_ptr<HittableObject> a, const shared_ptr<HittableObject> b) {
	return boxCompare(a, b, 1);
}

inline bool boxZCompare(const shared_ptr<HittableObject> a, const shared_ptr<HittableObject> b) {
	return boxCompare(a, b, 2);
}