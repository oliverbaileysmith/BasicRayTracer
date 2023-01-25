#pragma once

#include "HittableObjectList.h"

HittableObjectList::HittableObjectList() {}

HittableObjectList::HittableObjectList(std::shared_ptr<HittableObject> hittableObject) {
	add(hittableObject);
}

void HittableObjectList::clear() {
	m_HittableObjects.clear();
}

void HittableObjectList::add(std::shared_ptr<HittableObject> hittableObject) {
	m_HittableObjects.push_back(hittableObject);
}

bool HittableObjectList::Hit(const Ray &ray, double tMin, double tMax, HitRecord &hitRecord) const {
	HitRecord tempRecord;
	bool hitAnything = false;
	double closestSoFar = tMax;

	for (const auto &HittableObject : m_HittableObjects) {
		if (HittableObject->Hit(ray, tMin, closestSoFar, tempRecord)) {
			hitAnything = true;
			closestSoFar = tempRecord.m_T;
			hitRecord = tempRecord;
		}
	}

	return hitAnything;
}