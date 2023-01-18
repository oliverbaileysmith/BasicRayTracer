#include <iostream>
#include <fstream>

int main() {

	// Image properties

	const int IMAGE_WIDTH = 256;
	const int IMAGE_HEIGHT = 256;

	// Create output file

	std::ofstream outputFile;
	outputFile.open("output.ppm");
	
	// Render

	outputFile << "P3" << std::endl;
	outputFile << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << std::endl;
	outputFile << "255" << std::endl;

	for (int j = IMAGE_HEIGHT - 1; j >= 0; j--) {

		// Progress indicator
		std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < IMAGE_WIDTH; i++) {
			float r = (float)i / (float)(IMAGE_WIDTH - 1);
			float g = (float)j / (float)(IMAGE_HEIGHT - 1);
			float b = 0.25;

			int ir = (int)(255.999 * r);
			int ig = (int)(255.999 * g);
			int ib = (int)(255.999 * b);

			outputFile << ir << ' ' << ig << ' ' << ib << std::endl;
		}
	}

	// Close output file
	outputFile.close();

	return 0;
}