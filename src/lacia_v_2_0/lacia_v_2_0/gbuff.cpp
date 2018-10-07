
#include "gbuff.h"

#include "exception.h"
#include <cuda_runtime.h>

using namespace lacia;

gbuff::gbuff(count size) :
	_sz(size), _cpubuf(nullptr), _gpubuf(nullptr) {
	if (cudaMallocHost(&_cpubuf, sizeof(real) * size) != cudaSuccess) {
		CUDA_MEMMALLOC_FAIL();
	}
	if (cudaMalloc(&_gpubuf, sizeof(real) * size) != cudaSuccess) {
		CUDA_MEMMALLOC_FAIL();
	}
	memset(_cpubuf, 0, size * sizeof(real));
}
gbuff::~gbuff() {
	if (_cpubuf) {
		cudaFreeHost(_cpubuf);
		_cpubuf = nullptr;
	}
	if (_gpubuf) {
		cudaFree(_gpubuf);
		_gpubuf = nullptr;
	}
}

void gbuff::pull() {
	if (cudaMemcpy(_cpubuf, _gpubuf, sizeof(real) * _sz, cudaMemcpyDeviceToHost) != cudaSuccess) {
		CUDA_MEMCPY_FAIL();
	}
}
void gbuff::push() {
	if (cudaMemcpy(_gpubuf, _cpubuf, sizeof(real) * _sz, cudaMemcpyHostToDevice) != cudaSuccess) {
		CUDA_MEMCPY_FAIL();
	}
}
void gbuff::wait() {
	if (cudaDeviceSynchronize() != cudaSuccess) {
		CUDA_DEVSYNC_FAIL();
	}
}
