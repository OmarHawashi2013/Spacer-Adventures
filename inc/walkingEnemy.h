#pragma once

class walkingEnemy
{
public:
	float x = 0;
    float y = 0;
    int w = 64;
    int h = 64;
    float speed = 3;
    int dir = -1;

    bool onGround = false;
   	bool died = false;


    HDC dc;
	HBITMAP img;

	walkingEnemy(float initX, float initY, int initW, int initH, float sp){
		x = initX;
        y = initY;
        w = initW;
        h = initH;
        speed = sp;
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

	void update(Map *mp, HDC back) {
		if (!onGround)
			y += speed;
		onGround = false;

		for(int yl = 0; yl < mp->mapH;yl++){
			for(int xl = 0;xl < mp->mapW;xl++){
				if(mp->m[yl][xl] == '1' || mp->m[yl][xl] == '2'){
					float bx = xl * 64, by = yl * 64;
					if(collideDown(bx, by, 64, 64)){
						y = (by) - h;
						onGround = true;
					}
					if(collideUp(bx, by, 64, 64)){
						y = by + 64;
					}
				}
			}
		}
		x += speed * dir;

		for(int yl = 0; yl < mp->mapH; yl++){
	        for(int xl = 0; xl < mp->mapW; xl++){
	            if(mp->m[yl][xl] == '1' || mp->m[yl][xl] == '2'){
	                float bx = xl * 64, by = yl * 64;
	                if(collideLeft(bx, by, 64, 64)){
	                    x = bx + w;
	                    dir *= -1;
	                }
	                if(collideRight(bx, by, 64, 64)){
	                    x = bx - w;
	                    dir *= -1;
	                }
	            }
	        }
	    }

	    for (int i = 0; i < bv.size(); i++) {
		    if (collideUp(bv[i].x, bv[i].y, bv[i].w, bv[i].h)) {
		        died = true;
		        bv.erase(bv.begin() + i);
		        i--;
		    }
		}

		if (collideRight(player.x, player.y, player.w, player.h) || collideLeft(player.x, player.y, player.w, player.h)
			|| collideDown(player.x, player.y, player.w, player.h) || collideUp(player.x, player.y, player.w, player.h)
		) {
			playerHealth -= 1;
			if (playerHealth == 0){
				player.init(back, playerFrames[0], true);
				playerHealth = 100;
			}
		}
    }

	
};