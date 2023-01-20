#include <vector>

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/ext/vector_int3.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"

#include "Renderer.h"
#include "Ray.h"

float hitSphere(const glm::vec3 &sphereCenter, float sphereRadius, const Ray &ray) {
	glm::vec3 rayOriginToSphereCenter = ray.GetOrigin() - sphereCenter;
	float a = glm::dot(ray.GetDirection(), ray.GetDirection());
	float b = 2.0f * glm::dot(rayOriginToSphereCenter, ray.GetDirection());
	float c = glm::dot(rayOriginToSphereCenter, rayOriginToSphereCenter) - sphereRadius * sphereRadius;
	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0) {
		return -1.0f;
	} else {
		return (-b - sqrt(discriminant)) / (2.0f * a);
	}
}

glm::vec3 rayColour(const Ray &ray) {

	float t = hitSphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, ray);
	
	if (t > 0.0f) {
		glm::vec3 surfaceNormal = glm::normalize(ray.GetPositionAtDistance(t) - glm::vec3(0.0f, 0.0f, -1.0f));
		return 0.5f * glm::vec3(surfaceNormal.x + 1.0f, surfaceNormal.y + 1.0f, surfaceNormal.z + 1.0f);
	}

	glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
	t = 0.5f * (unitDirection.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}


void main() {

	// Image details

	const float IMAGE_ASPECT_RATIO = 16.0f / 9.0f;
	const int32_t IMAGE_WIDTH = 400;
	const int32_t IMAGE_HEIGHT = (int32_t)(IMAGE_WIDTH / IMAGE_ASPECT_RATIO);

	// Camera

	float viewportHeight = 2.0f;
	float viewportWidth = IMAGE_ASPECT_RATIO * viewportHeight;
	float focalLength = 1.0f;

	glm::vec3 cameraOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 viewportHorizontal = glm::vec3(viewportWidth, 0.0f, 0.0f);
	glm::vec3 viewportVertical = glm::vec3(0.0f, viewportHeight, 0.0f);
	glm::vec3 viewportLowerLeftCorner = cameraOrigin - viewportHorizontal / 2.0f - viewportVertical / 2.0f - glm::vec3(0.0f, 0.0f, focalLength);

	// Create image data

	std::vector<glm::ivec3> imageData;
	imageData.reserve(IMAGE_WIDTH * IMAGE_HEIGHT);

	for (int32_t y = IMAGE_HEIGHT - 1; y >= 0; y--) {

		for (int32_t x = 0; x < IMAGE_WIDTH; x++) {

			float u = (float)x / (float)(IMAGE_WIDTH - 1);
			float v = (float)y / (float)(IMAGE_HEIGHT - 1);

			Ray ray(cameraOrigin, viewportLowerLeftCorner + u * viewportHorizontal + v * viewportVertical - cameraOrigin);

			glm::ivec3 pixelColour = (glm::ivec3)(rayColour(ray) * 255.999f);

			imageData.emplace_back(pixelColour);
		}
	}

	// Render

	Renderer renderer;

	renderer.Render(IMAGE_WIDTH, IMAGE_HEIGHT, imageData);

}