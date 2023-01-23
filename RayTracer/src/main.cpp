#include "Util.h"
#include "Renderer.h"
#include "Ray.h"
#include "HittableObjectList.h"
#include "Sphere.h"

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/ext/vector_int3.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"

glm::vec3 rayColour(const Ray &ray, const HittableObject &scene) {

	HitRecord hitRecord;

	if (scene.Hit(ray, 0.0f, POSITIVE_INFINITY, hitRecord)) {
		return 0.5f * (hitRecord.m_Normal + glm::vec3(1.0f, 1.0f, 1.0f));
	}

	glm::vec3 unitDirection = glm::normalize(ray.GetDirection());
	float t = 0.5f * (unitDirection.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}


void main() {

	// Image details

	const float IMAGE_ASPECT_RATIO = 16.0f / 9.0f;
	const int32_t IMAGE_WIDTH = 400;
	const int32_t IMAGE_HEIGHT = (int32_t)(IMAGE_WIDTH / IMAGE_ASPECT_RATIO);

	// Scene

	HittableObjectList scene;
	scene.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
	scene.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

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

			glm::ivec3 pixelColour = (glm::ivec3)(rayColour(ray, scene) * 255.999f);

			imageData.emplace_back(pixelColour);
		}
	}

	// Render

	Renderer renderer;

	renderer.Render(IMAGE_WIDTH, IMAGE_HEIGHT, imageData);

}