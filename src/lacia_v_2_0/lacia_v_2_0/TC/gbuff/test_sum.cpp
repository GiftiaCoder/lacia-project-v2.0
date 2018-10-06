
#include "gbuff.h"
#include <gtest\gtest.h>

namespace lacia {

	static void sum_test(gbuff &src, gbuff &res) {
		res.sum(src);
		res.pull();
		std::cout << "begin sum :" << std::endl;
		for (count i = 0; i < res.size(); ++i) {
			std::cout << res[i] << ", ";
		}
		std::cout << std::endl;
	}
	TEST(gbuff_test, sum) {
		const count w = 13, h = 7;
		gbuff src(w * h);
		
		src.one();
		sum_test(src, gbuff(w));
		
		for (count i = 0; i < src.size(); ++i) {
			src[i] = i;
		}
		src.push();
		sum_test(src, gbuff(h));

		system("pause");
	}

}
