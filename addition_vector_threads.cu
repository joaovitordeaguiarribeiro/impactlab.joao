#include <iostream>
#include <vector>
#include <cuda_runtime.h>

__global__ void addVectors(float *a, float *b, float *c, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) {
        c[index] = a[index] + b[index];
    }
}

void verifyResult(const std::vector<float>& c, const std::vector<float>& a, const std::vector<float>& b) {
    const float tolerance = 1e-5;
    for (size_t i = 0; i < c.size(); ++i) {
        if (abs(c[i] - (a[i] + b[i])) > tolerance) {
            std::cout << "Erro no índice " << i << std::endl;
            return;
        }
    }
    std::cout << "Sucesso! Os resultados da GPU estão corretos." << std::endl;
}

int main() {
    int n = 1024 * 1024;
    size_t size = n * sizeof(float);

    std::vector<float> h_a(n);
    std::vector<float> h_b(n);
    std::vector<float> h_c(n);

    for (int i = 0; i < n; ++i) {
        h_a[i] = static_cast<float>(i);
        h_b[i] = static_cast<float>(i * 2);
    }

    float *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, h_a.data(), size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b.data(), size, cudaMemcpyHostToDevice);

    int threadsPerBlock = 256;
    int blocksPerGrid = (n + threadsPerBlock - 1) / threadsPerBlock;

    addVectors<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, n);

    cudaMemcpy(h_c.data(), d_c, size, cudaMemcpyDeviceToHost);
    
    cudaDeviceSynchronize();

    verifyResult(h_c, h_a, h_b);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
