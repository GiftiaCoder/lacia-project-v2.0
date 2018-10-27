
#include "gbuff.h"
#include <gtest\gtest.h>

#include "test_tools.h"

namespace lacia {

	TEST(gbuff_test, multiple) {

		const count w = 7, h = 11;

		gbuff a(w);
		a.one();
		a.multiple(1.414);
		print(a, "[1 ... 1] * 1.414 = ");

		gbuff b(w);
		b.set(0.618);
		b.multiple(a);
		print(b, "b * a = ");

		gbuff c(w);
		c.multiple(a, b);
		print(c, "a * b = ");

		gbuff d(w);
		d.multiple(a, 1.1);
		print(d, "a * 1.1 = ");

		gbuff x(w), y(h);
		for (count i = 0; i < w; ++i) {
			x[i] = i;
		}
		x.push();
		for (count i = 0; i < h; ++i) {
			y[i] = 0.1 * (real)i;
		}
		y.push();
		gbuff r(w * h);
		print(r, "r = ");
		r.cross(x, y);
		print(x, "x = ");
		print(y, "y = ");
		print(r, "r = x x y");

		r.one();
		for (count i = 0; i < w; ++i) {
			x[i] = i;
		}
		x.push();
		std::cout << r.size() << std::endl;
		std::cout << x.size() << std::endl;
		r.grouped_multiple(x);
		print(x, "x = ");
		print(r, "r = ");

		r.one();
		for (count i = 0; i < h; ++i) {
			y[i] = i;
		}
		y.push();
		r.grouped_multiple_t(y);
		print(y, "x = ");
		print(r, "r = ");

		system("pause");
	}

}
