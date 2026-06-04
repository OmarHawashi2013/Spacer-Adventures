#pragma once

class Back {
public:
	HDC dc;
	HBITMAP img;

	void init(HDC hdc, LPCSTR imgPath){
		dc = CreateCompatibleDC(hdc);

		img = (HBITMAP) LoadImageA(
			NULL,
			imgPath,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE
		);

		SelectObject(dc, img);
	}

	void render(HDC back) {
		BitBlt(
			back, 0, 0, 1280, 720, dc, 0, 0, SRCCOPY
		);
	}
};