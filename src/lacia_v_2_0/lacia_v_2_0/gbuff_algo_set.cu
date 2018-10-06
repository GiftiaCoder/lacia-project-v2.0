
#include "gbuff.h"

#include <cuda_runtime.h>

namespace lacia {

	__global__ void cualgo_set_value(real o[], count n, real v) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < n) {
			o[tid] = v;
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

	__device__ real cualgo_get_rand(real o[], count i, real min, real max) {
		union
		{
			struct {
				count a, b;
			};
			real *p;
		} u;
		u.p = o + i;
		real v = (((((((u.a ^ u.b) * 334379) >> 2) * 334363) >> 2) * 334349) >> 2) * 334333 / (real)(count)0xFFFFFFFF;
		return v * (max - min) + min;

	} 
	__global__ void cualgo_set_rand(real o[], count n, real min, real max) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < n) {
			o[tid] = cualgo_get_rand(o, tid, min, max);
			tid += tnm;
		}
	}
	void gbuff::rand(real min, real max) {
		cualgo_set_rand << <1024, 128 >> >(gpubuf(), size(), min, max);
	}

}
