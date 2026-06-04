#pragma once

class jumppad
{
public:
	float x = 0;
    float y = 0;
    int w = 64;
    int h = 64;


    HDC dc;
	HBITMAP img;

	jumppad(float initX, float initY, int initW, int initH){
		x = initX;
        y = initY;
        w = initW;
        h = initH;
    }

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

	void render(HDC back){
		TransparentBlt(
			back,
		    x - sub_x, y - sub_y, w, h,
		 	dc,
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

    bool collideDown(float bx, float by, float bw, float bh){
	    return (
	        y + h > by &&
	        y < by &&
	        x + w > bx &&
	        x < bx + bw
	    );
	}


    bool collideUp(float bx, float by, float bw, float bh){
	    return (
	        y < by + bh &&
	        y + h > by + bh &&
	        x + w > bx &&
	        x < bx + bw
	    );
	}


    bool collideRight(float bx, float by, float bw, float bh){
	    return (
	        x + w > bx &&
	        x < bx &&
	        y + h > by &&
	        y < by + bh
	    );
	}


    bool collideLeft(float bx, float by, float bw, float bh){
	    return (
	        x < bx + bw &&
	        x + w > bx + bw &&
	        y + h > by &&
	        y < by + bh
	    );
	}

	void update() {
		if (collideUp(player.x, player.y, player.w, player.h)) {
			velY = -50;
		}
	}
	
};