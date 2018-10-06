#ifndef __TEST_TOOLS_H__
#define __TEST_TOOLS_H__

#include "gbuff.h"

inline void print(lacia::gbuff &buf, const char *msg = ">\\") {
	std::cout << msg << std::endl;
	buf.pull();
	for (lacia::count i = 0; i < buf.size(); ++i) {
		std::cout << buf[i] << ", ";
	}
	std::cout << std::endl;
}

#endif