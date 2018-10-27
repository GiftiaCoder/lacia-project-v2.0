
#include "gbuff.h"
#include "gbuff_defs.cuh"

namespace lacia {

	__global__ void KERNEL_FUNC_NAME(cross)(real out[], real in1[], count group_size, real in2[], count calscale) {
		CREATE_TID(calscale)
			out[tid] = in1[tid % group_size] * in2[tid / group_size];
		DESTORY_TID()
	}
	void gbuff::cross(gbuff &in1, gbuff &in2) {
		count calscale = in1.size() * in2.size();
		CHECK_ASSERT(calscale == size(), INVALID_PARAMETER_FAIL);
		CALL_KERNEL_FUNC(cross, gpubuf(), in1.gpubuf(), in1.size(), in2.gpubuf(), calscale);
	}

	__global__ void KERNEL_FUNC_NAME(grouped_multiple)(real out[], count calscale, real in[], count group_size) {
		CREATE_TID(calscale)
			out[tid] *= in[tid % group_size];
		DESTORY_TID()
	}
	void gbuff::grouped_multiple(gbuff &in) {
		CHECK_ASSERT(size() % in.size() == 0, INVALID_PARAMETER_FAIL);
		CALL_KERNEL_FUNC(grouped_multiple, gpubuf(), size(), in.gpubuf(), in.size());
	}
	__global__ void KERNEL_FUNC_NAME(grouped_multiple)(real out[], real in1[], count calscale, real in2[], count group_size) {
		CREATE_TID(calscale)
			out[tid] = in1[tid] * in2[tid % group_size];
		DESTORY_TID()
	}
	void gbuff::grouped_multiple(gbuff &in1, gbuff &in2) {
		CHECK_ASSERT((size() == in1.size() && (size() % in2.size() == 0)), INVALID_PARAMETER_FAIL);
		CALL_KERNEL_FUNC(grouped_multiple, gpubuf(), in1.gpubuf(), in1.size(), in2.gpubuf(), in2.size());
	}

	__global__ void KERNEL_FUNC_NAME(grouped_multiple_t)(real out[], count calscale, real in[], count group_num) {
		CREATE_TID(calscale)
			out[tid] *= in[tid / group_num];
		DESTORY_TID()
	}
	void gbuff::grouped_multiple_t(gbuff &in) {
		CHECK_ASSERT(size() % in.size() == 0, INVALID_PARAMETER_FAIL);
		CALL_KERNEL_FUNC(grouped_multiple_t, gpubuf(), size(), in.gpubuf(), size() / in.size());
	}
	__global__ void KERNEL_FUNC_NAME(grouped_multiple_t)(real out[], real in1[], count calscale, real in2[], count group_num) {
		CREATE_TID(calscale)
			out[tid] = in1[tid] * in2[tid / group_num];
		DESTORY_TID()
	}
	void gbuff::grouped_multiple_t(gbuff &in1, gbuff &in2) {
		CHECK_ASSERT((size() == in1.size()) && (size() % in2.size() == 0), INVALID_PARAMETER_FAIL);
		CALL_KERNEL_FUNC(grouped_multiple_t, gpubuf(), in1.gpubuf(), in1.size(), in2.gpubuf(), in1.size() / in2.size());
	}

}
