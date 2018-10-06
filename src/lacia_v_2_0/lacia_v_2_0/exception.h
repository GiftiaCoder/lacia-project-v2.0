#ifndef __LACIA_EXCEPTION_H__
#define __LACIA_EXCEPTION_H__

#include <iostream>

#include <stdint.h>

namespace lacia {

	class exception {
	public:
		exception(const char *file, int line, uint64_t errcode, const char *detail);

		virtual void fatal();

	public:
		const char *_file;
		int _line;
		uint64_t _errcode;
		const char *_detail;
	};
#define THROW_EXCEPTION(__errcode__, __detail__) throw lacia::exception(__FILE__, __LINE__, __errcode__, __detail__)

#define CUDA_MEMMALLOC_FAIL() THROW_EXCEPTION(0x0001, "cuda memory malloc fail")
#define CUDA_MEMCPY_FAIL() THROW_EXCEPTION(0x0002, "cuda memcpy fail")
#define CUDA_DEVSYNC_FAIL() THROW_EXCEPTION(0x0002, "cuda device sync fail")

#define INVALID_PARAMETER_FAIL() THROW_EXCEPTION(0x0102, "invalid parameter")

}

std::ostream &operator<< (std::ostream &out, lacia::exception &exp);

#endif