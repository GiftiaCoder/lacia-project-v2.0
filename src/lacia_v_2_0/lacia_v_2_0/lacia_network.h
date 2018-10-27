#ifndef __LACIA_NETWORK_H__
#define __LACIA_NETWORK_H__

#include "lacia_reduct_layer.h"
#include "gbuff.h"

#include <mempool.h>

namespace lacia {

	class reduct_network {
	public :
		reduct_network(count innum, count laynum, const count outnum[], real weigain, real randmin, real randmax) {
			for (count layidx = 0; layidx < laynum; ++layidx) {
				_layers.construct(innum, outnum[layidx], weigain, randmin, randmax);
				innum = outnum[layidx];
			}
		}

	public:
		void output(gbuff &in, count layidx) {
			gbuff *p_in = &in;
			for (count lidx = 0; lidx < layidx; ++lidx) {
				_layers[lidx]->output(*p_in);
				p_in = &(_layers[lidx]->get_output());
			}
			_layers[layidx]->output(*p_in);
		}
		void output(gbuff &in, count layidx, real studyrate) {
			gbuff *p_in = &in;
			for (count lidx = 0; lidx < layidx; ++lidx) {
				_layers[lidx]->output(*p_in);
				p_in = &(_layers[lidx]->get_output());
			}
			_layers[layidx]->output(*p_in, studyrate);
		}
		void reduct(gbuff &out, count layidx) {
			gbuff *p_out = &out;
			for (count lidx = layidx; lidx > 0; --lidx) {
				_layers[lidx]->reduct(*p_out);
				p_out = &_layers[lidx]->get_reduct();
			}
		}

		gbuff &get_output() {
			return get_output(laynum() - 1);
		}
		gbuff &get_output(count layidx) {
			return _layers[layidx]->get_output();
		}
		gbuff &get_reduct() {
			return get_reduct(0);
		}
		gbuff &get_reduct(count layidx) {
			return _layers[layidx]->get_reduct();
		}

	public:
		inline count laynum() {
			return _layers.size();
		}

	public:
		void load(std::ifstream &in) {
			for (auto &e : _layers) {
				e->load(in);
			}
		}
		void save(std::ofstream &out) {
			for (auto &e : _layers) {
				e->save(out);
			}
		}

	private:
		memvec<reduct_layer, count, count, real, real, real> _layers;
	};

};

#endif