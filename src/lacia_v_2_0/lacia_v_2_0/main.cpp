
#include "gbuff.h"
#include "lacia_layer.h"
#include "exception.h"

#include <Windows.h>

static void print_output(lacia::gbuff &out) {
	for (int i = 0; i < out.size(); ++i) {
		std::cout << out[i] << ", ";
	}
	std::cout << std::endl;
}

int main() {

	const lacia::count innum = 100;
	const lacia::count outnum = 4;

	lacia::layer lay(innum, outnum);
	lacia::gbuff in(innum);
	lacia::gbuff targ(outnum), grad(outnum);

	for (int i = 0; i < innum; ++i) {
		in[i] = 0.01 * (lacia::real)i;
	}
	in.push();
	for (int i = 0; i < outnum; ++i) {
		targ[i] = 0.1 * (lacia::real)i;
	}
	targ.push();

	print_output(targ);

	while (true) {
		lay.output(in);
		
		grad.minus(targ, lay.get_output());
		grad.dot(0.1);

		lay.train(in, grad);

		grad.minus(targ, lay.get_output());
		//lay.get_output().pull();
		//print_output(lay.get_output());
		grad.pull();
		print_output(grad);

		//Sleep(200);
	}

	system("pause");
	return 0;
}
