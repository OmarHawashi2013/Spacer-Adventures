#pragma once

class bullet
{
public:
	HDC bulletDC;
	float x = 0, y = 0, xd = 20, yd = 0;
	int w = 16, h = 16;
	HBITMAP img;
	bool isCharged = false;

	int frame = 1;

	int at = 5;

	int flip = 1;

	void init(HDC hdc, LPCSTR imgPath){
		if (img) DeleteObject(img);
		if (bulletDC) DeleteDC(bulletDC);
		bulletDC = CreateCompatibleDC(hdc);

		img = (HBITMAP) LoadImageA(
			NULL,
			imgPath,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE
		);

		SelectObject(bulletDC, img);
	}

	void update(HDC back) {
		at --;

		if (at <= 0) {
			frame ++;

			at = 5;

			if (frame > 2) frame = 1;
		}

		x += xd * flip;
		y += yd;

		if (!isCharged){
			switch(frame) {
				case 1: init(back, "sprites/bullet1.bmp"); break;
				case 2: init(back, "sprites/bullet2.bmp"); break;
			}
		}
		else {
			switch(frame) {
				case 1: init(back, "sprites/charge_bullet1.bmp"); break;
				case 2: init(back, "sprites/charge_bullet2.bmp"); break;
			}	
		}
	}

	void render(HDC back){
		TransparentBlt(
			back,
		    x - sub_x, y - sub_y, w, h,
		 	bulletDC,
			0, 0, w, h,
			RGB(100, 100, 100)
		);

		if (ShowCollisions) {
			RECT r = {(int)(x - sub_x), (int)(y - sub_y), (int)(x+w-sub_x), (int)(y+h - sub_y)};
			FrameRect(back, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));

			char buf[64];
	        sprintf(buf, "x:%d y:%d", (int)x, (int)y);

	        HFONT oldFont = (HFONT)SelectObject(back, hFontSmall);
	        SetBkMode(back, TRANSPARENT);
	        SetTextColor(back, RGB(255,255,255));
	        TextOut(back, x - sub_x, y - 14 - sub_y, buf, strlen(buf));
	        SelectObject(back, oldFont);
		}
	}


	
	~bullet(){
		if (img) {
			DeleteObject(img);
		}
	}
	
};