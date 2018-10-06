
#include "gbuff.h"
#include <gtest\gtest.h>

#include "test_tools.h"

namespace lacia {

	TEST(gbuff_test, minus) {
		const count n = 7;

		gbuff a(n), b(n), c(n);

		for (count i = 0; i < a.size(); ++i) {
			a[i] = i;
		}
		a.push();
		print(a, "a = [0 - n]");

		b.one();

		a.dec(b);
		print(a, "a = a - b");

		c.minus(a, b);
		print(c, "c = a - b");

		c.dec(3.1419);
		print(c, "c -= 3.14159");

		a.minus(c, 0.618);
		print(a, "a = c - 0.618");

		system("pause");
	}

}
