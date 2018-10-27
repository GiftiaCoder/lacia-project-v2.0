
#include "image_res.h"

#pragma comment(lib, "FreeImage.lib")

namespace lacia {

	image_res::image_res(const char *imgpath, trans_b2r_func b2r, trans_r2b_func r2b) :
		_width(0), _height(0), _bmp(nullptr), _data(nullptr), 
		_r2b(r2b) {
		FREE_IMAGE_FORMAT fmt = FreeImage_GetFileType(imgpath);
		FIBITMAP *bmp = FreeImage_Load(fmt, imgpath);
		if (bmp) {
			if (FreeImage_GetImageType(bmp) != FIT_BITMAP ||
				FreeImage_GetColorType(bmp) != FIC_RGB) {
				std::cout << "image type: " << FreeImage_GetImageType(bmp) << std::endl
					<< "color type: " << FreeImage_GetColorType(bmp) << std::endl;
				FreeImage_Unload(bmp);
				return;
			}

			if (! load_image_data(bmp, b2r)) {
				FreeImage_Unload(bmp);
				return;
			}

			std::cout << "load image success: " << imgpath << std::endl;
		}
	}
	image_res::~image_res() {
		if (_bmp) {
			FreeImage_Unload(_bmp);
			_bmp = nullptr;
		}
		if (_data) {
			delete[] _data;
			_data = nullptr;
		}
		_width = 0;
		_height = 0;
	}

	bool image_res::get_data(int x, int y, int w, int h, gbuff &dst) {
		if ((x + w) > _width || (y + h) > _height || (w * h * 3) != dst.size()) {
			return false;
		}

		count offset = 0;
		real *addr = _data + (x + (y * _width)) * 3;
		for (int yi = 0; yi < h; ++yi) {
			dst.cpyfrom(offset, addr, w * 3);

			offset += (w * 3);
			addr += (_width * 3);
		}
		return true;
	}

	bool image_res::set_data(int x, int y, int w, int h, gbuff &res) {
		if ((x + w) > _width || (y + h) > _height || (w * h * 3 != res.size())) {
			return false;
		}

		count offset = 0;
		real *addr = _data + (x + (y * _width)) * 3;
		for (int yi = 0; yi < h; ++yi) {
			res.cpyto(offset, addr, w * 3);

			offset += (w * 3);
			addr += (_width * 3);
		}
		return true;
	}

	bool image_res::save(const char *path) {
		BYTE *bits = FreeImage_GetBits(_bmp);
		for (int i = 0; i < (_width * _height * 3); ++i) {
			bits[i] = _r2b(_data[i]);
		}
		return FreeImage_Save(FIF_PNG, _bmp, path) == TRUE;
	}

	bool image_res::load_image_data(FIBITMAP *bmp, trans_b2r_func b2r) {
		int width = FreeImage_GetWidth(bmp);
		int height = FreeImage_GetHeight(bmp);
		int size = width * height * 3;

		real *data = new real[size];
		if (! data) {
			std::cout << "malloc buffer fail, size: " << (size * sizeof(real)) << std::endl;
			return false;
		}

		BYTE *bits = FreeImage_GetBits(bmp);
		for (int i = 0; i < size; ++i) {
			data[i] = b2r(bits[i]);
		}

		_bmp = bmp;
		_data = data;
		_width = width;
		_height = height;

		return true;
	}

}
