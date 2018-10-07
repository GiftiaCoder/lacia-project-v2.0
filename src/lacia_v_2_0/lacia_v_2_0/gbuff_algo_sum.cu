
#include "gbuff.h"

#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

#include <device_functions.h>

namespace lacia {
	
	__global__ void cualgo_cpy_sum(real o[], real b[], count group_num, count group_size) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < group_num) {
			o[tid] = b[tid * group_size];
			tid += tnm;
		}
	}

	/*
	 * if group size is even, sum_offset = sum_size
	 * else, sum_offset = sum_size + 1
	*/
	__global__ void cualgo_naive_sum(real b[], count sum_size, count sum_offset, count group_size, count calculate_scale) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < calculate_scale) {
			count idx = ((tid / sum_size) * group_size) + (tid % sum_size);
			b[idx] += b[idx + sum_offset];
			tid += tnm;
		}
	}
	static void naive_sum(real o[], real b[], count group_size, count group_num) {
		count sum_size = group_size;
		while (true) {
			count sum_offset = sum_size & 0x1;
			if ((sum_size >>= 1) > 0) {
				cualgo_naive_sum << <1024, 128 >> >(b, sum_size, sum_size + sum_offset, group_size, sum_size * group_num);
				// cudaDeviceSynchronize(); // auto sync
				sum_size += sum_offset;
				continue;
			}
			break;
		}
		cualgo_cpy_sum << <1024, 128 >> >(o, b, group_num, group_size);
	}
	
	static void quick_sum(real o[], real b[], count gsz, count gnum) {
		// TODO
	}

	void gbuff::sum(gbuff &b) {
		if (b.size() % size() != 0) {
			INVALID_PARAMETER_FAIL();
		}

		naive_sum(gpubuf(), b.gpubuf(), b.size() / size(), size());
	}

}
