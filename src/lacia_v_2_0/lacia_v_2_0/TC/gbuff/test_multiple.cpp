
#include "gbuff.h"
#include <gtest\gtest.h>

#include "test_tools.h"

namespace lacia {

	TEST(gbuff_test, multiple) {

		const count w = 7, h = 11;

		gbuff a(w);
		a.one();
		a.dot(1.414);
		print(a, "[1 ... 1] * 1.414 = ");

		gbuff b(w);
		b.set(0.618);
		b.dot(a);
		print(b, "b * a = ");

		gbuff c(w);
		c.dot(a, b);
		print(c, "a * b = ");

		gbuff d(w);
		d.dot(a, 1.1);
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
		r.dot_multiple(x);
		print(x, "x = ");
		print(r, "r = ");

		r.one();
		for (count i = 0; i < h; ++i) {
			y[i] = i;
		}
		y.push();
		r.dot_multiple_t(y);
		print(y, "x = ");
		print(r, "r = ");

		system("pause");
	}

}
