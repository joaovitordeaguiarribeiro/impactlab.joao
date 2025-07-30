#include <iostream>
#include <cuda_runtime.h>

// __global__ define uma função (kernel) que roda na GPU
__global__ void olaCUDA() {
    printf("Olá, CUDA, direto da GPU!\n");
}

int main() {
    // A sintaxe <<<1, 1>>> chama o kernel para ser executado na GPU
    olaCUDA<<<1, 1>>>();

    // Sincroniza a CPU com a GPU para aguardar o término do kernel
    cudaDeviceSynchronize();

    return 0;
}
