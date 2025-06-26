#include <fstream> // Read and Write Images
#include <iostream> // Standard Input and Output

#include <chrono> // Timer

using namespace std;
using namespace std::chrono; // Timer

int main() { // Thread

// Read Image
	ifstream Image_Read;
	Image_Read.open("images/Input.ppm");
    
  
// Write Image
	ofstream Image_write;
	Image_write.open("images/output/input_out_G_R.ppm");

	// Copy Memory
	//Image_Read >> memory>> Image_Write

	//Image Header
	// Type = P3 ou P6
	string type = "", width = "", height = "", RGBMax = "";

	//int width = 0, height = 0, RGBMax = 0, red, g, b;

    
	// Copy Memory
	//Image_Read >> memory
	Image_Read >> type;
	Image_Read >> width;
	Image_Read >> height;
	Image_Read >> RGBMax;


	

	// Copy Memory to new Image
	//memory>> Image_Write
	Image_write << type << endl;
	Image_write << width << " " << height << endl;
	Image_write << RGBMax << endl;


	// Image Body
	string red = "", green = "", blue = "";

    std::cout << "Reading Image: " << type << " " << width << " " << height << " " << RGBMax << endl;

    std::cout << "Starting to read pixel data..." << endl;
    
    // Start Timer
    auto start = high_resolution_clock::now(); // Start Timer
    
	while (!Image_Read.eof()) { // ImageRead numero Pixel = 640 * 283 = 181.120 Pixels - 20Mbytes
        // Read RGB values
        //std::cout << "Reading RGB values..." << endl;

		// Read Image and Write to Memory
		Image_Read >> red;
		Image_Read >> green;
		Image_Read >> blue;

        // Converte String (red) to number(intRed) -- int num = std::stoi(str);
        
        int intRed = stoi(red);
        int intGreen = stoi(green);
        int intBlue = stoi(blue);
        //std::cout << "Red: " << intRed << ", Green: " << intGreen << ", Blue: " << intBlue << endl;

        //Filter RGB values to green
		intGreen = intGreen * 2; // Increase green value
		if (intGreen > 255) { // Ensure it does not exceed the maximum value
			intGreen = 255; // Cap it at 255
		}

		intRed = intRed / 2; // Decrease red value
		if (intRed < 0) { // Ensure it does not go below 0
			intRed = 0; // Cap it at 0
		}

        
		// Convert back to string for writing
		red = to_string(intRed);
		green = to_string(intGreen);
		blue = to_string(intBlue);


		// Memory to Write to new Images
		Image_write << red << " " << green << " " << blue << " " ;//<< endl;
	}
    auto end = high_resolution_clock::now(); // End Timer
    
    std::cout << "Finished reading pixel data." << endl;
    
    std::cout << "End Timer Image..." << endl;
    // Calculate duration  
    auto duration = duration_cast<milliseconds>(end - start);
    std::cout << "Read and Write Images Pixel Time: " << duration.count() << " ms" << std::endl;


	//  Close Images
	Image_Read.close();
	Image_write.close();





	return 0;

}
