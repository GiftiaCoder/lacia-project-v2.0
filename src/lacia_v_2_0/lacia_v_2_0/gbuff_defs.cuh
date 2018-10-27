#ifndef __GBUFF_DEFS_CUH__
#define __GBUFF_DEFS_CUH__

#include "common.h"

#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

#include <device_functions.h>

#define GRID_DIM (1024)
#define BLOCK_DIM (128)

#if 0
#define GRID_INFO
#else
#define GRID_INFO <<<GRID_DIM, BLOCK_DIM>>>
#endif

#define KERNEL_FUNC_NAME(_name_) cualgo_##_name_##_ops
#define CALL_KERNEL_FUNC(_name_, ...) KERNEL_FUNC_NAME(_name_) GRID_INFO (##__VA_ARGS__)

#define CREATE_TID(_calscale_) \
	count tnm = blockDim.x * gridDim.x; \
	count tid = blockIdx.x * blockDim.x + threadIdx.x; \
	while (tid < _calscale_) {
#define DESTORY_TID() \
		tid += tnm; \
	}

#define CHECK_ASSERT(_expr_, _exception_) \
	if (! (_expr_)) { \
		_exception_(); \
	}

#endif