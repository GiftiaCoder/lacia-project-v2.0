#ifndef __LACIA_REDUCT_LAYER_H__
#define __LACIA_REDUCT_LAYER_H__

#include "lacia_layer.h"
#include "gbuff.h"

#include <fstream>

namespace lacia {

	class reduct_layer {
	public:
		reduct_layer(count innum, count outnum, real weigain = (real)1.0, real rand_min = (real)-1.0, real rand_max = (real)1.0);
	
	public:
		void output(gbuff &in);
		void output(gbuff &in, real study_rate);
		void reduct(gbuff &targ);

	public:
		inline gbuff &get_output() {
			return _output.get_output();
		}
		inline gbuff &get_reduct() {
			return _reduct.get_output();
		}

	public:
		void load(std::ifstream &in) {
			in.read((char *)&_weigain, sizeof(_weigain));
			_output.load(in);
			_ograd.load(in);
			_reduct.load(in);
			_rgrad.load(in);
		}
		void save(std::ofstream &out) {
			out.write((const char *)&_weigain, sizeof(_weigain));
			_output.save(out);
			_ograd.save(out);
			_reduct.save(out);
			_rgrad.save(out);
		}

	private:
		real _weigain;

		layer _output;
		gbuff _ograd;

		layer _reduct;
		gbuff _rgrad;
	};

}

#endif