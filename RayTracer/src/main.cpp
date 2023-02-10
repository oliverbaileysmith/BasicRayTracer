#include <iostream>
#include <memory>

#include "Util.h"
#include "Renderer.h"
#include "Ray.h"
#include "HittableObjectList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"
#include "MovingSphere.h"
#include "AARect.h"
#include "Box.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scene.h"

#include "vendor/glm/ext/vector_double3.hpp"
#include "vendor/glm/gtx/vector_angle.hpp"

glm::dvec3 rayColour(const Ray &ray, const glm::dvec3 &BGColour, const HittableObject &scene, uint32_t maxRayBounces) {

	HitRecord hitRecord;

	if (maxRayBounces <= 0)
		return glm::dvec3(0.0, 0.0, 0.0);

	if (!scene.Hit(ray, 0.001, POSITIVE_INFINITY, hitRecord))
		return BGColour;
	
	Ray scattered;
	glm::dvec3 attenuation;
	glm::dvec3 emitted = hitRecord.m_MaterialPtr->emitted(hitRecord.m_U, hitRecord.m_V, hitRecord.m_HitPoint);

	if (!hitRecord.m_MaterialPtr->Scatter(ray, hitRecord, attenuation, scattered))
		return emitted;

	return emitted + attenuation * rayColour(scattered, BGColour, scene, maxRayBounces - 1);
}


void main() {

	// Scene

	Scene scene;
	scene.Construct1();

	// Image details

	const double IMAGE_ASPECT_RATIO = scene.m_Camera.m_ImageAspectRatio;
	const int32_t IMAGE_WIDTH = 600;
	const int32_t IMAGE_HEIGHT = (int32_t)(IMAGE_WIDTH / IMAGE_ASPECT_RATIO);
	const int32_t SAMPLES_PER_PIXEL = 200;
	const int32_t MAX_RAY_BOUNCES = 50;
	const glm::dvec3 BACKGROUND_COLOUR(0.0, 0.0, 0.0);
	const OutputFormat OUTPUT_FORMAT = OutputFormat::JPEG;

	Renderer renderer(IMAGE_WIDTH, IMAGE_HEIGHT);

	for (int32_t y = IMAGE_HEIGHT - 1; y >= 0; y--) {
		
		// Progress indicator
		std::cout << "\rScanlines remaining: " << y << ' ' << std::flush;

		for (int32_t x = 0; x < IMAGE_WIDTH; x++) {

			glm::dvec3 pixelColour(0.0, 0.0, 0.0);
			for (int s = 0; s < SAMPLES_PER_PIXEL; s++) {

				double u = ((double)x + randomDouble()) / (double)(IMAGE_WIDTH - 1);
				double v = ((double)y + randomDouble()) / (double)(IMAGE_HEIGHT - 1);

				Ray ray = scene.m_Camera.getRay(u, v);
				pixelColour += rayColour(ray, BACKGROUND_COLOUR, scene.m_HittableObjectList, MAX_RAY_BOUNCES);

			}
			renderer.RenderPixel(pixelColour, SAMPLES_PER_PIXEL);
		}
	}

	// Render

	std::cout << std::endl << "Writing output to file.";
	renderer.WriteOutput(IMAGE_WIDTH, IMAGE_HEIGHT, OUTPUT_FORMAT);

}