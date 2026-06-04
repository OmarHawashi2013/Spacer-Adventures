#pragma once

class gameObj {
public:
    float x = 0;
    float y = 0;
    int w = 64;
    int h = 64;
    float iX = 0; float iY = 0;

    float velX, velY;


    HDC dc;

	gameObj() {}

    gameObj(float initX, float initY, int initW, int initH){
    	iX = initX;
    	iY = initY;

        x = initX;
        y = initY;
        w = initW;
        h = initH;
    }

    void init(HDC hdc, HBITMAP img, bool initPlace){
    	if (initPlace){
			x = iX;
			y = iY;
		}
		
		if (dc) DeleteDC(dc);

		dc = CreateCompatibleDC(hdc);

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

	~gameObj() {
        if (dc) DeleteDC(dc);
    }
};
