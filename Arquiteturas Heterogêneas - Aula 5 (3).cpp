//Modulo_01_Aula_05-01.cpp

// STB Images

// This code uses the STB image library to load and manipulate images.
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "includes/stb_image.h"
#include "includes/stb_image_write.h"
#include <chrono> // Timer

#include <iostream>
#include <vector>
#include <thread> // Required for multithreading

using namespace std;
using namespace std::chrono; // Timer

// Function to process a chunk of the image
/*
Calculating Chunk Sizes:
Total_pixels: Represents the total number of bytes in the image (width * height * channels). We use long long to prevent potential overflow for very large images.
chunk_size: The total pixels are divided by the number of threads to determine how many pixels each thread will process.
*/
void processImageChunk(unsigned char* img_data, int start_index, int end_index) {
for (int i = start_index; i < end_index; ++i) {
img_data[i] = 255 - img_data[i]; // Invert color
}
}

int main ( ) {
// Load an image
int width, height, channels;

// Start Timer
auto start = high_resolution_clock::now(); // Start Timer

int x,y,n,ok;
ok= stbi_info("images/rostopics.png", &x, &y, &n);

// auto end = high_resolution_clock::now(); // End Timer

std::cout << "Image info: " << ok << " ok " << x << "x" << y << " with " << n << " channels." << std::endl;

// Start Timer
//auto start = high_resolution_clock::now(); // Start Timer
unsigned char* img = stbi_load("images/rostopics.png", &width, &height, &channels, 0);
//auto end = high_resolution_clock::now(); // End Timer

// Check if the image was loaded successfully
std::cout << "Image loaded: " << width << "x" << height << " with " << channels << " channels." << std::endl;

if (img == nullptr) {
std::cerr << "Error loading image 1" << std::endl;
return 1;
}

std::cout << "Image_Size = " << width * height *channels << std::endl;

// Multithreaded image processing
int num_threads = std::thread::hardware_concurrency(); // Get number of available cores
std::cout << "Number of available threads: " << num_threads << std::endl;

if (num_threads == 0) { // Fallback if hardware_concurrency returns 0
std::cout << "Warning: std::thread::hardware_concurrency() returned 0. Defaulting to 4 threads." << std::endl;
num_threads = 4;
}
std::cout << "Using " << num_threads << " threads for image processing." << std::endl;

long long total_pixels = static_cast<long long>(width) * height * channels;
long long chunk_size = total_pixels / num_threads;

std::vector<std::thread> threads;

// // Start Timer
// auto start = high_resolution_clock::now(); // Start Timer

for (int i = 0; i < num_threads; ++i) {
long long start_index = i * chunk_size;
long long end_index = (i == num_threads - 1) ? total_pixels : (start_index + chunk_size);
threads.emplace_back(processImageChunk, img, start_index, end_index);
}

// Wait for all threads to finish
for (std::thread& t : threads) {
t.join();
}

// auto end = high_resolution_clock::now(); // End Timer

std::cout << "Finished reading pixel data." << endl;

//auto end = high_resolution_clock::now(); // End Timer

// Save the modified image
stbi_write_jpg("images/output/stb_Output_2.jpg", width, height, channels, img, 100);

auto end = high_resolution_clock::now(); // End Timer
std::cout << "End Timer Image..." << endl;
// Calculate duration
auto duration = duration_cast<milliseconds>(end - start);
std::cout << "Read and Write Images Pixel Time: " << duration.count() << " ms" << std::endl;


// Free the image memory
stbi_image_free(img);

std::cout << "Image processed and saved successfully!" << std::endl;

return 0;
}
