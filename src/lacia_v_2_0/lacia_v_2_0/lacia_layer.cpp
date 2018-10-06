
#include "lacia_layer.h"

using namespace lacia;

layer::layer(count innum, count outnum) :
	_wei(innum * outnum), _bias(outnum), _out(outnum), 
	_tmp(innum * outnum) {
	_wei.rand(-0.07159, 0.07159);
	_bias.rand(-0.07159, 0.07159);
}
void layer::output(gbuff &in) {
	_tmp.dot_multiple(_wei, in);
	_out.sum(_tmp);
	_out.inc(_bias);
	_out.tanh();
}
void layer::train(gbuff &in, gbuff &grad) {
	_tmp.cross(in, grad);
	
	_wei.inc(_tmp);
	_bias.inc(grad);
}
void layer::train(gbuff &in, gbuff &grad, gbuff &igrad) {
	// calculate front layer grad
	_tmp.dot_multiple_t(_wei, grad);
	igrad.sum(_tmp);

	train(in, grad);
}
