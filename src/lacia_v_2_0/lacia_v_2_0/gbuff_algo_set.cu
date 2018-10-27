
#include "gbuff.h"
#include "gbuff_defs.cuh"

namespace lacia {

	__global__ void KERNEL_FUNC_NAME(set_value)(real out[], count calscale, real value) {
		CREATE_TID(calscale)
			out[tid] = value;
		DESTORY_TID()
	}
	void gbuff::zero() {
		set((real) 0.0);
	}
	void gbuff::one() {
		set((real) 1.0);
	}
	void gbuff::set(real value) {
		CALL_KERNEL_FUNC(set_value, gpubuf(), size(), value);
	}

	__device__ real KERNEL_FUNC_NAME(rand)(count seed, real min, real max) {
		count t = ((((((seed * 334379) >> 3) * 334363) >> 3) * 334349) >> 3) * 334333;
		real v = (real)t / (real)(count)0xFFFFFFFF;
		return v * (max - min) + min;

	} 
	__global__ void KERNEL_FUNC_NAME(rand)(real out[], count calscale, real min, real max, seed_t seed) {
		CREATE_TID(calscale)
			union {
				struct {
					count a;
					count b;
				};
				seed_t p;
			} u = { 0 };
			u.p = tid * sizeof(seed_t) + seed;
			out[tid] = KERNEL_FUNC_NAME(rand)(u.a ^ u.b, min, max);
		DESTORY_TID()
	}
	void gbuff::rand(real min, real max, seed_t seed) {
		if (! seed) {
			seed = (seed_t)gpubuf();
		}
		CALL_KERNEL_FUNC(rand, gpubuf(), size(), min, max, seed);
	}

}
