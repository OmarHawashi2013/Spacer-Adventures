#pragma once

class box {
public:
    float x = 0;
    float y = 0;
    int w = 64;
    int h = 64;
    float iX = 0; float iY = 0;

    bool onGround = false;

    float velX, velY;


    HDC dc;

	box() {}

    box(float initX, float initY, int initW, int initH){
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
		    (int)x - sub_x,(int) y - sub_y, w, h,
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

	void update(Map *mp) {
	    onGround = false;
	    float gravity = 3.0;

	    y += gravity;
	    
	    for(int ly = 0; ly < mp->mapH; ly++){
	        for(int lx = 0; lx < mp->mapW; lx++){
	            if(mp->m[ly][lx] == '1' || mp->m[ly][lx] == '2'){
	                float bx = lx * 64, by = ly * 64;
	                
	                if (y + h > by && y + h < by + 15 && x + w > bx && x < bx + 64) {
	                    y = by - h;
	                    onGround = true;
	                }
	            }
	        }
	    }

	    if (collideRight(player.x, player.y, player.w, player.h)) {
	        x -= speed;
	    } 
	    else if (collideLeft(player.x, player.y, player.w, player.h)) {
	        x += speed;
	    }
	    
	    for(int ly = 0; ly < mp->mapH; ly++){
	        for(int lx = 0; lx < mp->mapW; lx++){
	            if(mp->m[ly][lx] == '1' || mp->m[ly][lx] == '2'){
	                float bx = lx * 64;
	                if (x + w > bx && x < bx + 64 && y + h > ly*64 && y < (ly+1)*64) {
	                     if (x < bx) x = bx - w; 
	                     else if (x > bx) x = bx + 64;
	                }
	            }
	        }
	    }
	}

	~box() {
        if (dc) DeleteDC(dc);
    }
};
