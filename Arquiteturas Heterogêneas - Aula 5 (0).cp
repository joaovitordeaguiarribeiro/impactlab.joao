// STB Images

// This code uses the STB image library to load and manipulate images.
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "includes/stb_image.h"
#include "includes/stb_image_write.h"

#include <iostream>
#include <vector>

int main ( ) {
// Load an image
int width, height, channels;

int x,y,n,ok;
ok= stbi_info("images/rostopics.png", &x, &y, &n);
//ok = stbi_info("images/input.ppm", &x, &y, &n);

// returns ok=1 and sets x, y, n if image is a supported format,
// 0 otherwise.

std::cout << "Image info: " << ok << " ok " << x << "x" << y << " with " << n << " channels." << std::endl;


//unsigned char* img = stbi_load("images/input.ppm", &width, &height, &channels, 0);
unsigned char* img = stbi_load("images/rostopics.png", &width, &height, &channels, 0); // Load the image again for testing

// Check if the image was loaded successfully

std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << std::endl;

if (img == nullptr) {
std::cerr << "Error loading image 1" << std::endl;
return 1;
}

std::cout << "Image_Size = " << width * height *channels << std::endl;
// Process the image (for example, invert colors)
for (int i = 0; i < width * height * channels; i++) {
img[i] = 255 - img[i]; // Invert color
}

// Save the modified image

//stbi_write_png("images/output/stb_Output_1.png", width, height, channels, img, width * channels); // Use this for PNG format
stbi_write_jpg("images/output/stb_Output_2.jpg", width, height, channels, img, 100); // Use this for JPG format with quality 100

// Free the image memory
stbi_image_free(img);

std::cout << "Image processed and saved successfully!" << std::endl;

return 0;
}
