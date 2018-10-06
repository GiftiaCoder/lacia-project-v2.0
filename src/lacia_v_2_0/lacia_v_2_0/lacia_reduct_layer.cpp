
#include "lacia_reduct_layer.h"

using namespace lacia;

reduct_layer::reduct_layer(count innum, count outnum) : 
	_output(innum, outnum), _ograd(outnum), 
	_reduct(outnum, innum), _rgrad(innum) {
	// do nothing
}

void reduct_layer::output(gbuff &in) {
	_output.output(in);
}
void reduct_layer::output(gbuff &in, real study_rate) {
	_output.output(in);
	_reduct.output(_output.get_output());

	// calculate reduct part grad
	_rgrad.minus(in, _reduct.get_output());
	_rgrad.dot(study_rate);

	// train reduct part
	_reduct.train(_output.get_output(), _rgrad, _ograd);
	// train output part
	_output.train(in, _ograd);
}
void reduct_layer::reduct(gbuff &targ) {
	_reduct.output(targ);
}
