
#include "gbuff.h"

#include <cuda_runtime.h>

namespace lacia {

	__global__ void cualgo_dec_num(real o[], real v, count len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] -= v;
			tid += tnm;
		}
	}
	void gbuff::dec(real v) {
		cualgo_dec_num << <1024, 128 >> >(gpubuf(), v, size());
	}

	__global__ void cualgo_dec_vec(real o[], real a[], count len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] -= a[tid];
			tid += tnm;
		}
	}
	void gbuff::dec(gbuff &b) {
		if (size() != b.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dec_vec << <1024, 128 >> >(gpubuf(), b.gpubuf(), size());
	}

	__global__ void cualgo_minus_num(real o[], real a[], real v, count len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] = a[tid] - v;
			tid += tnm;
		}
	}
	void gbuff::minus(gbuff &b, real v) {
		if (size() != b.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_minus_num << <1024, 128 >> >(gpubuf(), b.gpubuf(), v, size());
	}

	__global__ void cualgo_minus_vec(real o[], real a[], real b[], count len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] = a[tid] - b[tid];
			tid += tnm;
		}
	}
	void gbuff::minus(gbuff &b1, gbuff &b2) {
		if (size() != b1.size() || size() != b2.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_minus_vec << <1024, 128 >> >(gpubuf(), b1.gpubuf(), b2.gpubuf(), size());
	}

}
