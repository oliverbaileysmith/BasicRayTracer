#pragma once

#include "Material.h"

Lambertian::Lambertian(const glm::dvec3 &albedo) : m_Albedo(std::make_shared<SolidColour>(albedo)) {}

Lambertian::Lambertian(std::shared_ptr<Texture> albedo) : m_Albedo(albedo) {}

bool Lambertian::Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const {
	glm::dvec3 scatterDirection = hitRecord.m_Normal + randomUnitVector();

	// Catch scatter direction close to zero
	if (nearZero(scatterDirection))
		scatterDirection = hitRecord.m_Normal;

	rayScattered = Ray(hitRecord.m_HitPoint, scatterDirection, rayIncident.GetTime());
	attenuation = m_Albedo->value(hitRecord.m_U, hitRecord.m_V, hitRecord.m_HitPoint);
	return true;
}

Metal::Metal(const glm::dvec3 &albedo, double fuzzFactor) : m_Albedo(albedo), m_Fuzz(fuzzFactor < 1 ? fuzzFactor : 1) {}

bool Metal::Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const {
	glm::dvec3 reflected = reflect(glm::normalize(rayIncident.GetDirection()), hitRecord.m_Normal);
	rayScattered = Ray(hitRecord.m_HitPoint, reflected + m_Fuzz * randomInUnitSphere(), rayIncident.GetTime());
	attenuation = m_Albedo;
	return (glm::dot(rayScattered.GetDirection(), hitRecord.m_Normal) > 0.0);
}

Dielectric::Dielectric(double refractiveIndex) : m_RefractiveIndex(refractiveIndex) {}

bool Dielectric::Scatter(const Ray &rayIncident, const HitRecord &hitRecord, glm::dvec3 &attenuation, Ray &rayScattered) const {
	attenuation = glm::dvec3(1.0, 1.0, 1.0);
	double refractionRatio = hitRecord.m_FrontFace ? (1.0 / m_RefractiveIndex) : m_RefractiveIndex;

	glm::dvec3 unitDirection = glm::normalize(rayIncident.GetDirection());
	double cosTheta = std::fmin(glm::dot(-unitDirection, hitRecord.m_Normal), 1.0);
	double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0;
	glm::dvec3 direction;

	if (cannotRefract || Reflectance(cosTheta, refractionRatio) > randomDouble())
		direction = reflect(unitDirection, hitRecord.m_Normal);
	else
		direction = refract(unitDirection, hitRecord.m_Normal, refractionRatio);

	rayScattered = Ray(hitRecord.m_HitPoint, direction, rayIncident.GetTime());
	return true;
}

double Dielectric::Reflectance(double cosine, double refractionRatio) {
	//Schlick's Approximation
	double r0 = (1.0 - refractionRatio) / (1.0 + refractionRatio);
	r0 *= r0;
	return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}