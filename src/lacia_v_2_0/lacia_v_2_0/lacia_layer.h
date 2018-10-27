#ifndef __LACIA_LAYER_H__
#define __LACIA_LAYER_H__

#include "gbuff.h"

namespace lacia {

	class layer {
	public:
		layer(count innum, count outnum, 
			real rand_min = (real)-1.0, real rand_max = (real)1.0);
		
	public:
		void output(gbuff &in, real weigain = (real)1.0);
		void train(gbuff &in, gbuff &grad);
		void train(gbuff &in, gbuff &grad, gbuff &igrad);

	public:
		inline gbuff &get_output() {
			return _out;
		}

	public:
		void load(std::ifstream &in) {
			_wei.load(in);
			_bias.load(in);
			_out.load(in);
			_tmp.load(in);
		}
		void save(std::ofstream &out) {
			_wei.save(out);
			_bias.save(out);
			_out.save(out);
			_tmp.save(out);
		}

	private:
		gbuff _wei, _bias;
		gbuff _out;

		gbuff _tmp;
	};

}

#endif