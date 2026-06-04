#pragma once
std::vector<bullet> rv;


class rocketShooter
{
public:
	
	float x = 0;
    float y = 0;
    int w = 64;
    int h = 64;

    int st = 30;

    HDC dc;
	HBITMAP img;

	rocketShooter(float initX, float initY, int initW, int initH){
		x = initX;
        y = initY;
        w = initW;
        h = initH;
    }

	void init(HDC hdc, LPCSTR imgPath){
		if (img) DeleteObject(img);
		if (dc) DeleteDC(dc);
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

	void update(HDC back) {
		st --;

		if (st <= 0){
			bullet rb;
			rb.xd = 10;

			rb.x = x + 32;
			rb.y = y + 32;
			rb.flip = 1;
			rb.init(back, "sprites/bullet1.bmp");

			rv.push_back(rb);

			bullet lb;
			lb.xd = 10;
			lb.x = x + 32;
			lb.y = y + 32;
			lb.flip = -1;
			lb.init(back, "sprites/bullet1.bmp");

			rv.push_back(lb);

			st = 30;
		}

		for (int i = rv.size() - 1; i >= 0; i--) {
		    rv[i].update(back);
		    rv[i].render(back);

		    int screenLeft   = sub_x - 100;
		    int screenRight  = sub_x + 1280 + 100;
		    int screenTop    = sub_y - 100;
		    int screenBottom = sub_y + 720 + 100;

		    if (rv[i].x < screenLeft || rv[i].x > screenRight || 
		        rv[i].y < screenTop  || rv[i].y > screenBottom) 
		    {
		        rv.erase(rv.begin() + i);
		    }
		}
	}
	
};