#ifndef __IMAGE_RES_H__
#define __IMAGE_RES_H__

#include "gbuff.h"
#include "FreeImage.h"

namespace lacia {

	class image_res {
	public:
		typedef real(*trans_b2r_func)(BYTE);
		typedef BYTE(*trans_r2b_func)(real);
		image_res(const char *imgpath, trans_b2r_func b2r, trans_r2b_func r2b);
		~image_res();

	public:
		bool get_data(int x, int y, int w, int h, gbuff &dst);
		bool set_data(int x, int y, int w, int h, gbuff &res);

		bool save(const char *path);

		inline int width() {
			return _width;
		}
		inline int height() {
			return _height;
		}

	private:
		FIBITMAP *_bmp;
		real *_data;
		int _width, _height;

	private:
		bool load_image_data(FIBITMAP *bmp, trans_b2r_func b2r);

		trans_r2b_func _r2b;
	};

}

#endif