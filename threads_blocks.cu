#include <iostream>
#include <vector>
#include <numeric>
#include <cuda_runtime.h>

__global__ void addVectors2D(float *a, float *b, float *c, int n) {
    int threadsPerBlock = blockDim.x * blockDim.y;
    int blockOffset = blockIdx.x * threadsPerBlock;
    int threadOffset = threadIdx.y * blockDim.x + threadIdx.x;
    int index = blockOffset + threadOffset;

    if (index < n) {
        c[index] = a[index] + b[index];
    }
}

void verify(const std::vector<float>& c, int n) {
    for (int i = 0; i < n; ++i) {
        if (c[i] != 3.0f * i) {
            std::cout << "Erro na verificação no índice " << i << std::endl;
            return;
        }
    }
    std::cout << "Sucesso! O resultado da GPU está correto." << std::endl;
}

int main() {
    const int n = 1048576; // 2^20
    const size_t size = n * sizeof(float);

    std::vector<float> h_a(n);
    std::vector<float> h_b(n);
    std::vector<float> h_c(n);

    for(int i = 0; i < n; ++i) {
        h_a[i] = static_cast<float>(i);
        h_b[i] = static_cast<float>(i * 2);
    }

    float *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, h_a.data(), size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b.data(), size, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    int numBlocks = (n + (threadsPerBlock.x * threadsPerBlock.y) - 1) / (threadsPerBlock.x * threadsPerBlock.y);
    dim3 gridDim(numBlocks);

    addVectors2D<<<gridDim, threadsPerBlock>>>(d_a, d_b, d_c, n);
    
    cudaMemcpy(h_c.data(), d_c, size, cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();

    verify(h_c, n);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
