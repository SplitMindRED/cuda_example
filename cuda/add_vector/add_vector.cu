#include <cuda.h>

#include "add_vector.hpp"

using std::cout;
using std::endl;

__global__ void add_vector(float* out, float* a, float* b, int n)
{
  // int i = blockIdx.x * blockDim.x + threadIdx.x;
  // for (int i = 0; i < n; i++)
  // {
  //   out[i] = a[i] + b[i];
  // }

  int index = 0;
  int stride = blockDim.x;

  // index = threadIdx.x + blockIdx.x * blockDim.x;
  // index = threadIdx.x + threadIdx.x * blockDim.x;

  for (int i = threadIdx.x; i < n; i += stride)
  {
    // out[i] = a[i] + b[i];
    out[i] = threadIdx.x;
  }

  // out[threadIdx.x] = threadIdx.x;
}

int cu_add_vector(float* out, float* a, float* b, int N)
{
  float *d_a, *d_b, *d_out;
  cudaError_t err;

  cudaMalloc(&d_out, N * sizeof(float));
  cudaMalloc(&d_a, N * sizeof(float));
  cudaMalloc(&d_b, N * sizeof(float));

  cudaMemcpy(d_a, a, N * sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, N * sizeof(float), cudaMemcpyHostToDevice);

  // block, threads
  // add_vector<<<1, 1>>>(d_out, d_a, d_b, N);
  add_vector<<<1, 8>>>(d_out, d_a, d_b, N);

  cudaError_t errSync = cudaGetLastError();
  cudaError_t errAsync = cudaDeviceSynchronize();
  if (errSync != cudaSuccess)
  {
    printf("Sync kernel error: %s\n", cudaGetErrorString(errSync));
  }
  if (errAsync != cudaSuccess)
  {
    printf("Async kernel error: %s\n", cudaGetErrorString(errAsync));
  }

  cudaDeviceSynchronize();

  err = cudaMemcpy(out, d_out, N * sizeof(float), cudaMemcpyDeviceToHost);
  if (err != cudaSuccess)
  {
    cout << "err: " << cudaGetErrorString(err) << endl;
  }

  cudaFree(d_out);
  cudaFree(d_a);
  cudaFree(d_b);

  return 0;
}