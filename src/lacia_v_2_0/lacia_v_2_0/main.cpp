
#include "main.h"

#include "lacia_layer.h"
#include "TC/gbuff/test_tools.h"

int _network_demo() {
	const lacia::count innum(512), outnum(8);
	
	lacia::layer lay(innum, outnum);
	lacia::gbuff in(innum);
	lacia::gbuff targ(outnum), grad(outnum);

	for (int i = 0; i < targ.size(); ++i) {
		targ[i] =  (lacia::real)i / (lacia::real)(targ.size() * 2);
	}
	targ.push();
	//print(targ);

	for (int i = 0; i < in.size(); ++i) {
		in[i] = (lacia::real)i / (lacia::real)(in.size() * 2);
	}
	in.push();
	//print(in);

	while (true) {
		lay.output(in);

		grad.minus(targ, lay.get_output());
		print(grad, "diff = ");

		grad.dot(0.001);

		lay.train(in, grad);
	}

	return 0;
}
