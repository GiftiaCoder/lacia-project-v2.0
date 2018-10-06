
#include "exception.h"

using namespace lacia;

exception::exception(const char *file, int line, uint64_t errcode, const char *detail) : 
	_file(file), _line(line), _errcode(errcode), _detail(detail) {
}

void exception::fatal() {
	std::cout << __FUNCSIG__ << std::endl;
}

std::ostream &operator<< (std::ostream &out, lacia::exception &exp) {
	out << "DBG> location : " << exp._file << ':' << exp._line << std::endl;
	out << "DBG> errcode  : 0x" << std::hex << exp._errcode << std::oct << std::endl;
	out << "DBG> detail   : " << exp._detail << std::endl;
	return out;
}
