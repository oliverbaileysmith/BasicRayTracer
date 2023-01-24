#include <iostream>

#include "Util.h"
#include "Renderer.h"
#include "Ray.h"
#include "HittableObjectList.h"
#include "Sphere.h"
#include "Camera.h"

#include "vendor/glm/ext/vector_float3.hpp"
#include "vendor/glm/ext/vector_int3.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"

glm::vec3 rayColour(const Ray &ray, const HittableObject &scene, uint32_t maxRayBounces) {

	HitRecord hitRecord;

	if (maxRayBounces <= 0)
		return glm::vec3(0.0f, 0.0f, 0.0f);

	if (scene.Hit(ray, 0.0f, POSITIVE_INFINITY, hitRecord)) {
		glm::vec3 diffuseTarget = hitRecord.m_HitPoint + hitRecord.m_Normal + randomInUnitSphere();
		return 0.5f * rayColour(Ray(hitRecord.m_HitPoint, diffuseTarget - hitRecord.m_HitPoint), scene, maxRayBounces - 1);
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
	const int32_t SAMPLES_PER_PIXEL = 100;
	const int32_t MAX_RAY_BOUNCES = 50;

	// Scene

	HittableObjectList scene;
	scene.add(std::make_shared<Sphere>(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f));
	scene.add(std::make_shared<Sphere>(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f));

	// Camera

	Camera camera;

	// Create image data

	std::vector<glm::ivec3> imageData;
	imageData.reserve(IMAGE_WIDTH * IMAGE_HEIGHT);

	for (int32_t y = IMAGE_HEIGHT - 1; y >= 0; y--) {
		
		// Progress indicator
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int32_t x = 0; x < IMAGE_WIDTH; x++) {

			glm::ivec3 pixelColour(0, 0, 0);
			for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {

				float u = ((float)x + randomFloat()) / (float)(IMAGE_WIDTH - 1);
				float v = ((float)y + randomFloat()) / (float)(IMAGE_HEIGHT - 1);

				Ray ray = camera.getRay(u, v);
				pixelColour += (glm::ivec3)(rayColour(ray, scene, MAX_RAY_BOUNCES) * 255.999f);

			}

			imageData.emplace_back(pixelColour / SAMPLES_PER_PIXEL);
		}
	}

	// Render

	Renderer renderer;

	renderer.Render(IMAGE_WIDTH, IMAGE_HEIGHT, imageData);

}