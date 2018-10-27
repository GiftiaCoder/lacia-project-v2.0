
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
		void cpyfrom(count offset, real src[], count len);
		void cpyto(count offset, real dst[], count len);

	public:
		void push();
		void pull();
		void wait();

		void load(std::ifstream &in);
		void save(std::ofstream &out);

	public:
		void zero();
		void one();
		void set(real value);
		void rand(real min, real max, seed_t seed = 0L);

#define DEC_GBUFF_VALUE_OPS(_name_) \
	void _name_(real val); \
	void _name_(gbuff &in, real val);
#define DEC_GBUFF_GBUFF_OPS(_name_) \
	void _name_(gbuff &in); \
	void _name_(gbuff &in1, gbuff &in2);
#define DEC_GBUFF_ALL_OPS(_name_) \
	DEC_GBUFF_VALUE_OPS(_name_) \
	DEC_GBUFF_GBUFF_OPS(_name_)

		DEC_GBUFF_ALL_OPS(plus)
		DEC_GBUFF_ALL_OPS(minus)
		DEC_GBUFF_ALL_OPS(multiple)
		DEC_GBUFF_ALL_OPS(divide)

		DEC_GBUFF_GBUFF_OPS(grouped_multiple)
		DEC_GBUFF_GBUFF_OPS(grouped_multiple_t)

		void cross(gbuff &b1, gbuff &b2);

		void sum(gbuff &b);

	public:
		void tanh();
		void tanhex();
		void cut();
		
		void relu();
		void prelu();
		void elu();
		void selu();

	private:
		count _sz;
		real *_cpubuf;
		real *_gpubuf;
	};

}

#endif
