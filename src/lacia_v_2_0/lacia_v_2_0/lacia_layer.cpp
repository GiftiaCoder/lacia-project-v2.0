
#include "lacia_layer.h"

using namespace lacia;

layer::layer(count innum, count outnum, real rand_min, real rand_max) :
	_wei(innum * outnum), _bias(outnum), _out(outnum),
	_tmp(innum * outnum) {
	_wei.rand(rand_min, rand_max);
	_bias.rand(rand_min, rand_max);
}
void layer::output(gbuff &in, real weigain) {
	_tmp.grouped_multiple(_wei, in);
	_out.sum(_tmp);
	_out.multiple(weigain);
	_out.plus(_bias);
	_out.elu();
}
void layer::train(gbuff &in, gbuff &grad) {
	_bias.plus(grad);

	_tmp.cross(in, grad);
	_wei.plus(_tmp);
}
void layer::train(gbuff &in, gbuff &grad, gbuff &igrad) {
	// calculate front layer grad
	_tmp.grouped_multiple_t(_wei, grad);
	igrad.sum(_tmp);

	train(in, grad);
}
