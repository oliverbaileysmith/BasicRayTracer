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

bool HittableObjectList::buildAABB(double time0, double time1, AABB &outputAABB) const {

	if (m_HittableObjects.empty())
		return false;

	AABB tempBox;
	bool firstBox = true;

	for (const auto &object : m_HittableObjects) {
		if (!object->buildAABB(time0, time1, tempBox)) return false;
		outputAABB = firstBox ? tempBox : buildSurroundingAABB(outputAABB, tempBox);
		firstBox = false;
	}

	return true;
}