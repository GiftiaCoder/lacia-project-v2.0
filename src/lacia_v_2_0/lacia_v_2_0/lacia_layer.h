#ifndef __LACIA_LAYER_H__
#define __LACIA_LAYER_H__

#include "gbuff.h"

namespace lacia {

	class layer {
	public:
		layer(count innum, count outnum);

	public:
		void output(gbuff &in);
		void train(gbuff &in, gbuff &grad);
		void train(gbuff &in, gbuff &grad, gbuff &igrad);

	public:
		inline gbuff &get_output() {
			return _out;
		}

	private:
		gbuff _wei, _bias;
		gbuff _out;

		gbuff _tmp;
	};

}

#endif