
#include "gbuff.h"

#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

#include <device_functions.h>

namespace lacia {

	__global__ void cualgo_set_value(real o[], count n, real v) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < n) {
			o[tid] = (double)v;
			tid += tnm;
		}
	}
	void gbuff::zero() {
		set((real) 0.0);
	}
	void gbuff::one() {
		set((real) 1.0);
	}
	void gbuff::set(real v) {
		cualgo_set_value<<<1024, 128>>>(gpubuf(), size(), v);
	}

	__device__ real cualgo_get_rand(count seed, real min, real max) {
		count t = ((((((seed * 334379) >> 3) * 334363) >> 3) * 334349) >> 3) * 334333;
		real v = (real)t / (real)(count)0xFFFFFFFF;
		return v * (max - min) + min;

	} 
	__global__ void cualgo_set_rand(real o[], count n, real min, real max) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < n) {

			union {
				struct {
					count a;
					count b;
				};
				real *p;
			} u;
			u.p = o + tid;

			o[tid] = cualgo_get_rand(u.a ^ u.b, min, max);
			tid += tnm;
		}
	}
	void gbuff::rand(real min, real max) {
		cualgo_set_rand << <1024, 128 >> >(gpubuf(), size(), min, max);
	}

}
