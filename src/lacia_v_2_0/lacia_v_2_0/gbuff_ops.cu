
#include "gbuff.h"
#include "gbuff_defs.cuh"

namespace lacia {

#define DEF_GBUFF_DOT_OPS(_name_, _ops_) \
	__global__ void KERNEL_FUNC_NAME(_name_)(real out[], real dot, count calscale) { \
		CREATE_TID(calscale) \
			out[tid] _ops_##= dot; \
		DESTORY_TID() \
	} \
	__global__ void KERNEL_FUNC_NAME(_name_)(real out[], real in[], real dot, count calscale) { \
		CREATE_TID(calscale) \
			out[tid] = in[tid] _ops_ dot; \
		DESTORY_TID() \
	} \
	void gbuff::_name_(real dot) { \
		CALL_KERNEL_FUNC(_name_, gpubuf(), dot, size()); \
	} \
	void gbuff::_name_(gbuff &in, real dot) { \
		CHECK_ASSERT(size() == in.size(), INVALID_PARAMETER_FAIL); \
		CALL_KERNEL_FUNC(_name_, gpubuf(), in.gpubuf(), dot, size()); \
	}
#define DEF_GBUFF_1D_OPS(_name_, _ops_) \
	__global__ void KERNEL_FUNC_NAME(_name_)(real out[], real in[], count calscale) { \
		CREATE_TID(calscale) \
			out[tid] _ops_##= in[tid]; \
		DESTORY_TID() \
	} \
	__global__ void KERNEL_FUNC_NAME(_name_)(real out[], real in1[], real in2[], count calscale) { \
		CREATE_TID(calscale) \
			out[tid] = in1[tid] _ops_ in2[tid]; \
		DESTORY_TID() \
	} \
	void gbuff::_name_(gbuff &in) { \
		CHECK_ASSERT(size() == in.size(), INVALID_PARAMETER_FAIL); \
		CALL_KERNEL_FUNC(_name_, gpubuf(), in.gpubuf(), size()); \
	} \
	void gbuff::_name_(gbuff &in1, gbuff &in2) { \
		CHECK_ASSERT((size() == in1.size()) && (size() == in2.size()), INVALID_PARAMETER_FAIL); \
		CALL_KERNEL_FUNC(_name_, gpubuf(), in1.gpubuf(), in2.gpubuf(), size()); \
	}
#define DEF_GBUFF_NORMAL_OPS(_name_, _ops_) \
	DEF_GBUFF_DOT_OPS(_name_, _ops_) \
	DEF_GBUFF_1D_OPS(_name_, _ops_)

	DEF_GBUFF_NORMAL_OPS(plus, +)
	DEF_GBUFF_NORMAL_OPS(minus, -)
	DEF_GBUFF_NORMAL_OPS(multiple, *)
	DEF_GBUFF_NORMAL_OPS(divide, / )

}
