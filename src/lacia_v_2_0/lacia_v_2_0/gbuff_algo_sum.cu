
#include "gbuff.h"
#include "gbuff_defs.cuh"

namespace lacia {
	
	__global__ void KERNEL_FUNC_NAME(cpy_sum_result)(real out[], real sum_buf[], count group_num, count group_size) {
		CREATE_TID(group_num)
			out[tid] = sum_buf[tid * group_size];
		DESTORY_TID()
	}

	/*
	 * if group size is even, sum_offset = sum_size
	 * else, sum_offset = sum_size + 1
	*/
	__global__ void KERNEL_FUNC_NAME(naive_sum)(real sum_buf[], count sum_size, count sum_offset, count group_size, count calscale) {
		CREATE_TID(calscale)
			count idx = ((tid / sum_size) * group_size) + (tid % sum_size);
			sum_buf[idx] += sum_buf[idx + sum_offset];
		DESTORY_TID()
	}
	static void naive_sum(real out[], real in[], count group_size, count group_num) {
		count sum_size = group_size;
		while (true) {
			count sum_offset = sum_size & 0x1;
			if ((sum_size >>= 1) > 0) {
				CALL_KERNEL_FUNC(naive_sum, in, sum_size, sum_size + sum_offset, group_size, sum_size * group_num);
				// cudaDeviceSynchronize(); // auto sync
				sum_size += sum_offset;
				continue;
			}
			break;
		}
		CALL_KERNEL_FUNC(cpy_sum_result, out, in, group_num, group_size);
	}
	
	static void quick_sum(real o[], real b[], count gsz, count gnum) {
		// TODO
	}

	void gbuff::sum(gbuff &sum_buf) {
		CHECK_ASSERT(sum_buf.size() % size() == 0, INVALID_PARAMETER_FAIL);
		naive_sum(gpubuf(), sum_buf.gpubuf(), sum_buf.size() / size(), size());
	}

}
