
#include "gbuff.h"
#include <gtest\gtest.h>

#include "test_tools.h"

namespace lacia {

	TEST(gbuff_test, add) {
		const count n = 17;

		gbuff a(n), b(n), c(n);
		
		for (count i = 0; i < a.size(); ++i) {
			a[i] = i;
		}
		a.push();
		print(a, "a = [0 - n]");

		b.one();
		
		a.inc(b);
		print(a, "a = a + b");

		c.add(a, b);
		print(c, "c = a + b");

		c.inc(3.1419);
		print(c, "c += 3.14159");

		a.add(c, 0.618);
		print(a, "a = c + 0.618");

		system("pause");
	}

}
