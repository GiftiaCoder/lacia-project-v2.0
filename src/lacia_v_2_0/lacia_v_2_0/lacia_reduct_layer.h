#ifndef __LACIA_REDUCT_LAYER_H__
#define __LACIA_REDUCT_LAYER_H__

#include "lacia_layer.h"
#include "gbuff.h"

namespace lacia {

	class reduct_layer {
	public:
		reduct_layer(count innum, count outnum);
	
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

	private:
		layer _output;
		gbuff _ograd;

		layer _reduct;
		gbuff _rgrad;
	};

}

#endif