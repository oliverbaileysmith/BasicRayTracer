#pragma once

#include "Util.h"
#include "Ray.h"
#include "HittableObject.h"

struct HitRecord;

class Material {
public:
	virtual bool Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const = 0;
};

class Lambertian : public Material {
public:
	Lambertian(const glm::dvec3 &albedo);

	virtual bool Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const override;

private:
	glm::dvec3 m_Albedo;
};

class Metal : public Material {
public:
	Metal(const glm::dvec3 &albedo, double fuzzFactor);
	
	virtual bool Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const override;

private:
	glm::dvec3 m_Albedo;
	double m_Fuzz;
};