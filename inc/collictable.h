#pragma once

HDC collictableDC;

class collictable
{
public:
	float x = 0, y = 0, bx = 0, by = 0;
	int w = 32, h = 32;
	HBITMAP img;
	bool used = false;
	int st = 0;

	collictable(float initX, float initY, int initW, int initH){
		x = initX;
        y = initY;
        w = initW;
        h = initH;
    }

	void init(HDC hdc, LPCSTR imgPath){
		bx = x;
		by = y;
		if (img) DeleteObject(img);
		if (collictableDC) DeleteDC(collictableDC);
		collictableDC = CreateCompatibleDC(hdc);

		img = (HBITMAP) LoadImageA(
			NULL,
			imgPath,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE
		);

		SelectObject(collictableDC, img);
	}

	void update(HDC back) {
		st++;

		y = by + sin(st * 0.05) * 10;

		if (player.collideRight(x, y, w, h)) {
			used = true;
			mciSendString("play sndJump from 0", NULL, 0, NULL);
		}
	}

	void render(HDC back){
		TransparentBlt(
			back,
		    x - sub_x, y - sub_y, w, h,
		 	collictableDC,
			0, 0, w, h,
			RGB(100, 100, 100)
		);

		if (ShowCollisions) {
			RECT r = {(int)(x - sub_x), (int)(y - sub_y), (int)(x+w - sub_x), (int)(y+h - sub_y)};
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


	
	~collictable(){
		if (img) {
			DeleteObject(img);
		}
	}
	
};