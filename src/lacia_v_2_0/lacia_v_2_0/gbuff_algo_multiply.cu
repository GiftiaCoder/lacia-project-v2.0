
#include "gbuff.h"

#include <cuda_runtime.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

#include <device_functions.h>

namespace lacia {

	__global__ void cualgo_dot_num(real o[], real v, int len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] *= v;
			tid += tnm;
		}
	}
	void gbuff::dot(real v) {
		cualgo_dot_num << <1024, 128 >> > (gpubuf(), v, size());
	}

	__global__ void cualgo_dot_vec(real o[], real a[], int len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] *= a[tid];
			tid += tnm;
		}
	}
	void gbuff::dot(gbuff &b) {
		if (size() != b.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dot_vec << <1024, 128 >> >(gpubuf(), b.gpubuf(), size());
	}

	__global__ void cualgo_dot_num(real o[], real a[], real v, int len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] = a[tid] * v;
			tid += tnm;
		}
	}
	void gbuff::dot(gbuff &b, real v) {
		cualgo_dot_num<<<1024, 128>>>(gpubuf(), b.gpubuf(), v, size());
	}

	__global__ void cualgo_dot_vec(real o[], real a[], real b[], int len) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < len) {
			o[tid] = a[tid] * b[tid];
			tid += tnm;
		}
	}
	void gbuff::dot(gbuff &b1, gbuff &b2) {
		if (size() != b1.size() || size() != b2.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dot_vec<<<1024, 128>>>(gpubuf(), b1.gpubuf(), b2.gpubuf(), size());
	}

	__global__ void cualgo_cross(real o[], real a[], count group_size, real b[], count calculate_scale) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < calculate_scale) {
			o[tid] = a[tid % group_size] * b[tid / group_size];
			tid += tnm;
		}
	}
	void gbuff::cross(gbuff &b1, gbuff &b2) {
		if (b1.size() * b2.size() != size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_cross<<<1024, 128>>>(gpubuf(), b1.gpubuf(), b1.size(), b2.gpubuf(), b1.size() * b2.size());
	}

	__global__ void cualgo_dot_multiple(real o[], count calculate_scale, real a[], count group_size) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < calculate_scale) {
			o[tid] *= a[tid % group_size];
			tid += tnm;
		}
	}
	void gbuff::dot_multiple(gbuff &b) {
		if (size() % b.size() != 0) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dot_multiple<<<1024, 128>>>(gpubuf(), size(), b.gpubuf(), b.size());
	}

	__global__ void cualgo_dot_multiple_t(real o[], count calculate_scale, real a[], count group_num) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < calculate_scale) {
			o[tid] *= a[tid / group_num];
			tid += tnm;
		}
	}
	void gbuff::dot_multiple_t(gbuff &b) {
		if (size() % b.size() != 0) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dot_multiple_t<<<1024, 128>>>(gpubuf(), size(), b.gpubuf(), size() / b.size());
	}

	__global__ void cualgo_dot_multiple(real o[], real a[], count calculate_scale, real b[], count group_size) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < calculate_scale) {
			o[tid] = a[tid] * b[tid % group_size];
			tid += tnm;
		}
	}
	void gbuff::dot_multiple(gbuff &b1, gbuff &b2) {
		if (size() % b2.size() != 0 || size() != b1.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dot_multiple<<<1024, 128>>>(gpubuf(), b1.gpubuf(), b1.size(), b2.gpubuf(), b2.size());
	}

	__global__ void cualgo_dot_multiple_t(real o[], real a[], count calculate_scale, real b[], count group_num) {
		count tnm = blockDim.x * gridDim.x;
		count tid = blockIdx.x * blockDim.x + threadIdx.x;
		while (tid < calculate_scale) {
			o[tid] = a[tid] * b[tid / group_num];
			tid += tnm;
		}
	}
	void gbuff::dot_multiple_t(gbuff &b1, gbuff &b2) {
		if (size() % b2.size() != 0 || size() != b1.size()) {
			INVALID_PARAMETER_FAIL();
		}
		cualgo_dot_multiple_t<<<1024, 128>>>(gpubuf(), b1.gpubuf(), b1.size(), b2.gpubuf(), b1.size() / b2.size());
	}

}
