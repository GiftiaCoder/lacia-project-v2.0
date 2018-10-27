
#include "lacia_reduct_layer.h"

using namespace lacia;

reduct_layer::reduct_layer(count innum, count outnum, real weigain, 
	real rand_min, real rand_max) :
	_output(innum, outnum, rand_min, rand_max), _ograd(outnum),
	_reduct(outnum, innum, rand_min, rand_max), _rgrad(innum),
	_weigain(1 / (real)weigain){
	// do nothing
}

void reduct_layer::output(gbuff &in) {
	_output.output(in, _weigain);
}
void reduct_layer::output(gbuff &in, real study_rate) {
	_output.output(in, _weigain);
	_reduct.output(_output.get_output(), _weigain);

	// calculate reduct part grad
	_rgrad.minus(in, _reduct.get_output());
	_rgrad.multiple(study_rate);

	// train reduct part
	_reduct.train(_output.get_output(), _rgrad, _ograd);
	// train output part
	_output.train(in, _ograd);
}
void reduct_layer::reduct(gbuff &targ) {
	_reduct.output(targ);
}
