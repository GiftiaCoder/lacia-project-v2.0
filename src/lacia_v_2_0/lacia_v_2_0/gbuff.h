
#ifndef __LACIA_GBUFF_H__
#define __LACIA_GBUFF_H__

#include "common.h"
#include "exception.h"

namespace lacia {

	class gbuff {
	public:
		gbuff(count sz);
		~gbuff();

		inline count size() {
			return _sz;
		}
		inline real *cpubuf() {
			return _cpubuf;
		}
		inline real *gpubuf() {
			return _gpubuf;
		}
		inline real &operator[] (count idx) {
			return _cpubuf[idx];
		}
		inline real *operator() () {
			return gpubuf();
		}

	public:
		void push();
		void pull();
		void wait();

	public:
		void zero();
		void one();
		void set(real v);
		void rand(real min, real max);

		// this += v
		void inc(real v);
		// this += b
		void inc(gbuff &b);
		// this = b + v
		void add(gbuff &b, real v);
		// this = b1 + b2
		void add(gbuff &b1, gbuff &b2);

		// this -= v
		void dec(real v);
		// this -= b
		void dec(gbuff &b);
		// this = b - v
		void minus(gbuff &b, real v);
		// this = b1 - b2
		void minus(gbuff &b1, gbuff &b2);

		// this *= v
		void dot(real v);
		// this *= b (dot)
		void dot(gbuff &b);
		// this = b * v
		void dot(gbuff &b, real v);
		// this = b1 * b2 (dot)
		void dot(gbuff &b1, gbuff &b2);
		// this = b1 * b2 (cross)
		void cross(gbuff &b1, gbuff &b2);
		// this *= b (dot multiple)
		void dot_multiple(gbuff &b);
		// this *= b (dot multiple)
		void dot_multiple_t(gbuff &b);
		// this = b1 * b2 (dot multiple)
		void dot_multiple(gbuff &b1, gbuff &b2);
		// this = b1 * b2 (dot multiple transformed)
		void dot_multiple_t(gbuff &b1, gbuff &b2);

		void sum(gbuff &b);

		void tanh();
		void tanhex();

	private:
		count _sz;
		real *_cpubuf;
		real *_gpubuf;
	};

}

#endif
