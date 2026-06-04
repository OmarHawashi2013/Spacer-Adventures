#pragma once
gameObj player(64, 64, 64, 64);

int speed = 7;
float velY = 0;
bool onGround = false;
int jumpForce = 40 - 8;
int animTimer = 5;
int frame = 1;
int flip = 1;
int playerHealth = 100;

HBITMAP playerFrames[11];

int cyoteTimer = 5;

std::vector<bullet> bv;

void InitPlayerFrames() {
	playerFrames[0] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/player1.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[1] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/player2.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[2] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/player3.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[3] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/player4.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[4] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/player5.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[5] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/flippedPlayer1.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[6] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/flippedPlayer2.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[7] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/flippedPlayer3.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[8] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/flippedPlayer4.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );

    playerFrames[9] = (HBITMAP) LoadImageA(
        NULL,
        "sprites/flippedPlayer5.bmp",
        IMAGE_BITMAP,
        0, 0,
        LR_LOADFROMFILE
    );
}

void UpdatePlayerAnim(HDC back){
	animTimer--;
	if(animTimer <= 0){
		if(onGround and !Input::hold(VK_RIGHT) and !Input::hold(VK_LEFT)){
			frame++; animTimer=15; if(frame>2) frame=1;
		}
		else if(onGround and Input::hold(VK_RIGHT) and Input::hold(VK_LEFT)){
			frame++; animTimer=15; if(frame>2) frame=1;
		}
		else if(onGround and (Input::hold(VK_RIGHT) or Input::hold(VK_LEFT))){
			frame++;
			animTimer=10;
			if(frame>5)
				frame=3;
		}
		else {
			frame=3;
		}
	}
	else if(!onGround)
		frame=3;

	switch(flip){
		case 1:
			switch(frame){
				case 1: player.init(back,playerFrames[0],false); break;
				case 2: player.init(back,playerFrames[1],false); break;
				case 3: player.init(back,playerFrames[2],false); break;
				case 4: player.init(back,playerFrames[3],false); break;
				case 5: player.init(back,playerFrames[4],false); break;
			}
			break;
		case -1:
			switch(frame){
				case 1: player.init(back,playerFrames[5],false); break;
				case 2: player.init(back,playerFrames[6],false); break;
				case 3: player.init(back,playerFrames[7],false); break;
				case 4: player.init(back,playerFrames[8],false); break;
				case 5: player.init(back,playerFrames[9],false); break;
			}
			break;
	}
}

float gravity = 3.0f;
float smooth = 0.2f;

void UpdatePlayer(Map *mp, std::vector<platform>& v, HDC back){
	velY += gravity * smooth;
	player.y += velY;
	onGround = false;

	for(int y = 0; y < mp->mapH; y++){
		for(int x  =0;x < mp->mapW;x++){
			if(mp->m[y][x] == '1' || mp->m[y][x] == '2'){
				float bx = (x *64), by = (y * 64);
				if(player.collideDown(bx, by, 64, 64)){
					player.y=(by) - player.h;
					velY = 0;
					onGround = true;
				}
				if(player.collideUp(bx, by, 64, 64)){
					player.y = by + 64;
					velY = 0;
				}
			}
		}
	}

	if(Input::hold(VK_RIGHT)){
		flip = 1;
		player.x += speed;
		for(int y = 0;y < mp->mapH;y++){
			for(int x = 0;x < mp->mapW; x++){
				if(mp->m[y][x] == '1'|| mp->m[y][x] == '2'){
					float bx = (x *64), by = (y * 64);
					if(player.collideRight(bx, by, 64, 64)){
						player.x = bx - player.w;
					}
				}
			}
		}
	}
	if(Input::hold(VK_LEFT)){
		flip =- 1;
		player.x -= speed;
		for(int y = 0; y < mp->mapH;y++){
			for(int x = 0;x < mp->mapW;x++){
				if(mp->m[y][x] == '1' || mp->m[y][x] == '2'){
					float bx = (x *64), by = (y * 64);
					if(player.collideLeft(bx, by , 64, 64)){
						player.x = bx + player.w;
					}
				}
			}
		}
	}

	for (platform& f : v) {
		f.update(mp, back);
		f.render(back);

		float bx = f.x, by = f.y;
		if (velY >= 0 && (player.y + player.h) <= by + velY + 10 && !Input::hold(VK_DOWN)) { 
	        if (player.collideDown(bx, by, f.w, f.h)) {
	            player.y = by - player.h;
	            velY = 0;
	            onGround = true;
	            cyoteTimer = 5;
	            player.x += f.speed * f.dir;

	            for(int y = 0; y < mp->mapH; y++){
				    for(int x = 0; x < mp->mapW; x++){
				        if(mp->m[y][x] == '1' || mp->m[y][x] == '2'){
				            float bx = x * 64, by = y * 64;
				            if(player.collideRight(bx, by, 64, 64)) player.x = bx - player.w;
				            if(player.collideLeft(bx, by, 64, 64))  player.x = bx + 64;
				        }
				    }
				}
	        }
	    }
	}

	bool canJump = false;

	if (!onGround) {
		cyoteTimer --;
	}
	else {
		cyoteTimer = 5;
		canJump = true;
	}

	if (cyoteTimer > 0) {
		canJump = true;
	}

	if(Input::pressed(VK_Z) && canJump){
		velY = -jumpForce * 0.5;
		mciSendString("play sndJump from 0", NULL, 0, NULL);
		cyoteTimer = 0;
	}
//	if (Input::pressed(VK_Z)) {
//		gravity *= -1;
//	}
	if(Input::released(VK_Z) && !onGround) velY *= 0.5;

}

int ct = 60;
int cti = 60;

void renderUI(HDC back){
	char buf[64];
	sprintf(buf, "HEALTH %d", (int)playerHealth);

	HFONT oldFont = (HFONT)SelectObject(back, hFontSmall);
    SetBkMode(back, TRANSPARENT);
    SetTextColor(back, RGB(255,255,255));
    TextOut(back, 0, 0, buf, strlen(buf));
    SelectObject(back, oldFont);
}

void playerShoot(HDC back){
	if (Input::pressed(VK_X)){
		bullet nb;
		nb.x = player.x + 32;
		nb.y = player.y + 32;
		nb.flip = flip;

		if (Input::hold(VK_DOWN) and !onGround) {
			nb.yd = 20;
			nb.xd = 0;
			velY -= 20;
		}
		else if (Input::hold(VK_UP)) {
			nb.yd = -20;
			nb.xd = 0;
			velY += 20;
		}
		else {
			nb.yd = 0;
			if (Input::hold(VK_C)) {
				if (!Input::hold(VK_RIGHT) and !Input::hold(VK_LEFT)) {
					nb.xd = 20;
				}
				else {
					nb.xd = 40;	
				}
			}
			else {
				nb.xd = 20;
			}
		}


		nb.init(back, "sprites/bullet1.bmp");

		bv.push_back(nb);

		mciSendString("play sndShoot from 0", NULL, 0, NULL);
	}

	if (Input::hold(VK_X)) {
		ct --;
	}

	if (Input::released(VK_X)){
		if (ct < 0) {
			bullet nb;
			nb.x = player.x + 32;
			nb.y = player.y + 32;
			nb.flip = flip;
			nb.isCharged = true;

			if (Input::hold(VK_DOWN) and !onGround) {
				nb.yd = 20;
				nb.xd = 0;
				velY -= 40;
			}
			else if (Input::hold(VK_UP)) {
				nb.yd = -20;
				nb.xd = 0;
				velY += 40;
			}
			else {
				nb.yd = 0;
				if (Input::hold(VK_C)) {
					if (!Input::hold(VK_RIGHT) and !Input::hold(VK_LEFT)) {
						nb.xd = 20;
					}
					else {
						nb.xd = 40;	
					}
				}
				else {
					nb.xd = 20;
				}
			}

			nb.init(back, "sprites/bullet1.bmp");

			bv.push_back(nb);

			mciSendString("play sndShoot from 0", NULL, 0, NULL);
		}

		ct = cti;
	}

	for (int i = bv.size() - 1; i >= 0; i--) {
	    bv[i].update(back);
	    bv[i].render(back);

	    int screenLeft   = sub_x - 100;
	    int screenRight  = sub_x + 1280 + 100;
	    int screenTop    = sub_y - 100;
	    int screenBottom = sub_y + 720 + 100;

	    if (bv[i].x < screenLeft || bv[i].x > screenRight || 
	        bv[i].y < screenTop  || bv[i].y > screenBottom) 
	    {
	        bv.erase(bv.begin() + i);
	    }
	}
}

void updateCamera() {
	//sub_x = player.x - (1280/2);
	//sub_y = player.y - (720/2);

	sub_x = lerp(sub_x ,player.x - (1280/2), 0.2);
	sub_y = lerp(sub_y, player.y - (720/2), 0.2);
}

void playerRun() {
	if (Input::hold(VK_C)) {
		speed = 7 * 3;
		//jumpForce = 16 + 8;
	}
	else {
		speed = 12;
		//jumpForce = 40 - 8;
	}
}

