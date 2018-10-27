
#include "gbuff.h"
#include "gbuff_defs.cuh"

namespace lacia {
	
#define PRELU_A (0.01)
#define ELU_A (1.0)

#define SELU_A (1.0)
#define SELU_B (1.0)

#define DEF_ACTIVATE_FUNC(_name_) \
	__global__ void KERNEL_FUNC_NAME(_name_)(real value[], count calscale) { \
		CREATE_TID(calscale) \
			value[tid] = KERNEL_FUNC_NAME(_name_)(value[tid]); \
		DESTORY_TID() \
	} \
	void gbuff::_name_() { \
		CALL_KERNEL_FUNC(_name_, gpubuf(), size()); \
	}
	/****************************
	 * begin activate functions *
	 ****************************/
	__device__ real KERNEL_FUNC_NAME(tanh)(real val) {
		return tanh((double) val);
	}
	DEF_ACTIVATE_FUNC(tanh)

	__device__ real KERNEL_FUNC_NAME(tanhex)(real val) {
		return val * 0.001 + tanh((double)val);
	}
	DEF_ACTIVATE_FUNC(tanhex)

	__device__ real KERNEL_FUNC_NAME(cut)(real val) {
		return val < -1.0 ? -1.0 : (val > 1.0 ? 1.0 : val);
	}
	DEF_ACTIVATE_FUNC(cut)

	__device__ real KERNEL_FUNC_NAME(relu)(real val) {
		return val >= 0.0 ? val : 0.0;
	}
	DEF_ACTIVATE_FUNC(relu)
	
	__device__ real KERNEL_FUNC_NAME(prelu)(real val) {
		return val >= 0.0 ? val : (PRELU_A * val);
	}
	DEF_ACTIVATE_FUNC(prelu)

	__device__ real KERNEL_FUNC_NAME(elu)(real val) {
		return val >= 0.0 ? val : (ELU_A * (exp(val) - 1.0));
	}
	DEF_ACTIVATE_FUNC(elu)

	__device__ real KERNEL_FUNC_NAME(selu)(real val) {
		return SELU_B * (val >= 0.0 ? val : (SELU_A * (exp(val) - 1)));
	}
	DEF_ACTIVATE_FUNC(selu)

}
