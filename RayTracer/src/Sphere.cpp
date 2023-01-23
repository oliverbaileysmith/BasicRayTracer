#pragma once

#include "Sphere.h"

#include "vendor/glm/gtx/norm.hpp"

Sphere::Sphere(glm::vec3 center, float radius)
	: m_Center(center), m_Radius(radius)
{}

bool Sphere::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const {

    glm::vec3 rayOriginToSphereCenter = ray.GetOrigin() - m_Center;
    float a = glm::length2(ray.GetDirection());
    float halfB = glm::dot(rayOriginToSphereCenter, ray.GetDirection());
    float c = glm::length2(rayOriginToSphereCenter) - m_Radius * m_Radius;

    float discriminant = halfB * halfB - a * c;
    if (discriminant < 0)
        return false;
    float sqrtDiscriminant = sqrt(discriminant);

    float root = (-halfB - sqrtDiscriminant) / a;
    if (root < tMin || root > tMax) {
        root = (-halfB + sqrtDiscriminant) / a;
        if (root < tMin || root > tMax)
            return false;
    }

    hitRecord.m_T = root;
    hitRecord.m_HitPoint = ray.GetPositionAtDistance(hitRecord.m_T);
    glm::vec3 outwardNormal = (hitRecord.m_HitPoint - m_Center) / m_Radius;
    hitRecord.m_SetFaceNormal(ray, outwardNormal);

    return true;

}