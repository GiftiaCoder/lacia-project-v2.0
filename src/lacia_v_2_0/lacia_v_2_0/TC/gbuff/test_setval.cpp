
#include "gbuff.h"
#include <gtest\gtest.h>

#include "test_tools.h"

namespace lacia {

	TEST(gbuff_test, setval) {
		gbuff buf(11);

		buf.rand(-1.0, 1.0);
		print(buf);

		buf.zero();
		print(buf);

		buf.one();
		print(buf);

		buf.set(3.141);
		print(buf);

		buf.set(0.618);
		print(buf);

		system("pause");
	}

}
