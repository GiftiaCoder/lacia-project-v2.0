
#include "gbuff.h"

#include <cuda_runtime.h>

namespace lacia {
	
	__global__ void cualgo_tanh(real o[], real b[], count n) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < n) {
			o[tid] = tanh(b[tid]);
			tid += tnm;
		}
	}
	void gbuff::tanh() {
		cualgo_tanh << <1024, 128 >> > (gpubuf(), gpubuf(), size());
	}

	__global__ void cualgo_tanhex(real o[], real b[], count n) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < n) {
			o[tid] = 1.7159 * tanh(b[tid] * 0.6666);
			tid += tnm;
		}
	}
	void gbuff::tanhex() {
		cualgo_tanhex << <1024, 128 >> > (gpubuf(), gpubuf(), size());
	}

}
