#pragma once

#include <stdio.h>
#include <iostream>

extern "C"
{
  int cu_add_vector(float* out, float* a, float* b, int N);
}
