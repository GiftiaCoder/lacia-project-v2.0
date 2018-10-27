
#include "main.h"

#include "mempool.h"

#include "lacia_network.h"
#include "image_res.h"

lacia::real trans_b2r(BYTE val) {
	return (lacia::real)val / (255.0 * 10.0);
}
BYTE trans_r2b(lacia::real val) {
	int ret = (int)(val * (255.0 * 10.0));
	if (ret < 0) {
		return 0;
	}
	else if (ret > 255) {
		return 255;
	}
	return (BYTE)ret;
}

int _network_demo() {
	const char imgpath[] = "E:\\4K±ÚÖ½ (2).jpg";
	
	lacia::image_res res(imgpath, trans_b2r, trans_r2b);
	lacia::image_res dst(imgpath, trans_b2r, trans_r2b);

	const lacia::count innum = 32 * 32 * 3;
	const lacia::count laynum = 5;
	const lacia::count outnum[laynum] = {
		1024 * 8, 
		1024, 
		256, 
		64, 
		16, 
	};
	lacia::reduct_network network(
		innum, laynum, outnum, (lacia::real)10.0, (lacia::real)pow(10.0, -32), (lacia::real)pow(10.0, -32));



	const lacia::count step = 4;

	while (true) {
		// train loop
		// get result
		// save result and network
	}

	system("pause");
	return 0;
}
