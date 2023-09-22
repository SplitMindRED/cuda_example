#include <chrono>
#include <iostream>

extern "C"
{
#include "cuda/add_vector/add_vector.hpp"
#include "cuda/saxpy/saxpy.hpp"
}

#define N 1e7

using std::cout;
using std::endl;

void vector_add(float* out, float* a, float* b, int n)
{
  for (int i = 0; i < n; i++)
  {
    out[i] = a[i] + b[i];
  }
}

int main()
{
  cout << " Hello" << endl;

  float *a, *b, *out;

  auto cpu_start = std::chrono::high_resolution_clock::now();

  // Allocate memory
  a = (float*)malloc(sizeof(float) * N);
  b = (float*)malloc(sizeof(float) * N);
  out = (float*)malloc(sizeof(float) * N);

  // Initialize array
  for (int i = 0; i < N; i++)
  {
    a[i] = 1.0f;
    b[i] = 2.0f;
    out[i] = -1;
  }

  // CPU add vectors
  vector_add(out, a, b, N);
  auto cpu_stop = std::chrono::high_resolution_clock::now();

  auto gpu_saxpy_start = std::chrono::high_resolution_clock::now();
  // cu_saxpy();
  auto gpu_saxpy_stop = std::chrono::high_resolution_clock::now();

  auto gpu_start = std::chrono::high_resolution_clock::now();
  cu_add_vector(out, a, b, N);
  auto gpu_stop = std::chrono::high_resolution_clock::now();

  // cout << "out: " << out[(int)(N - 1)] << endl;
  // for (int i = 0; i < N; i++)
  // {
  //   cout << "i: " << i << " " << out[i] << endl;
  // }

  auto cpu_duration = std::chrono::duration_cast<std::chrono::microseconds>(cpu_stop - cpu_start);
  auto gpu_duration = std::chrono::duration_cast<std::chrono::microseconds>(gpu_stop - gpu_start);
  auto gpu_saxpy_duration = std::chrono::duration_cast<std::chrono::microseconds>(gpu_saxpy_stop - gpu_saxpy_start);
  std::cout << "gpu saxpy time: " << (float)gpu_saxpy_duration.count() / 1000.0 << " ms" << std::endl;
  std::cout << "cpu time: " << (float)cpu_duration.count() / 1000.0 << " ms" << std::endl;
  std::cout << "gpu time: " << (float)gpu_duration.count() / 1000.0 << " ms" << std::endl;

  free(a);
  free(b);
  free(out);

  cout << "end of main" << endl;

  return 0;
}