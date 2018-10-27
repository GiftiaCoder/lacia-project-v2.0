#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

#include <stdint.h>
#include <vector>

template<typename T, typename ... args_t>
class memitem {
public:
	~memitem() {
		((T *)data)->T::~T();
	}
public:
	inline T &construct(args_t ... args) {
		return *(new(data) T(args ...));
	}
public:
	inline T &operator*() {
		return *(T *)data;
	}
	inline T *operator->() {
		return (T *)data;
	}
private:
	uint8_t data[sizeof(T)];
};
template<typename T, typename ... args_t>
class memvec : public std::vector<memitem<T, args_t ...>> {
public:
	memvec() {
		reserve(32);
	}

	inline T &construct(args_t ... args) {
		size_type sz = size();
		if (sz >= capacity()) {
			reserve(sz + (sz >> 1));
		}
		resize(sz + 1);
		return (*this)[sz].construct(args ...);
	}
};

#endif