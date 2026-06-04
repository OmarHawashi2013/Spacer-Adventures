#pragma once

int selected = 0;

std::random_device rd;
std::mt19937 gen(rd());

void main_menu(HDC back) {
	if (Input::pressed(VK_UP)) {
		selected --;
		mciSendString("play sndJump from 0", NULL, 0, NULL);
	}
	if (Input::pressed(VK_DOWN)) {
		selected ++;
		mciSendString("play sndJump from 0", NULL, 0, NULL);
	}

	if (selected > 1) {
		selected = 0;
	}
	if (selected < 0) {
		selected = 1;
	}

	if (Input::pressed(VK_RETURN) and selected == 0) {
		gameState = 1;
		mciSendString("close bgm", NULL, 0, NULL);
		mciSendString("open music/music.wav type mpegvideo alias bgm", NULL, 0, NULL);
    	mciSendString("play bgm repeat", NULL, 0, NULL);
	}

	HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));

	std::uniform_int_distribution<> x_range(0, 1280);
	std::uniform_int_distribution<> y_range(0, 720);
	std::uniform_int_distribution<> c_range(0, 255);

	for (int i = 0; i < 40; ++i) {
		int x = x_range(gen);
		int y = y_range(gen);

		HBRUSH hBrush = CreateSolidBrush(RGB(c_range(gen), c_range(gen), c_range(gen)));

		SelectObject(back, hBrush);

		Rectangle(back, x, y, x + 8, y + 8);

		DeleteObject(hBrush);
	}


	HFONT oldFont = (HFONT)SelectObject(back, hFont);
	SetBkMode(back, TRANSPARENT);
	SetTextColor(back, RGB(255,255,255));

	if (selected == 0) {
		TextOut(back, 1280/2, 720/2, "> play", 6);
		TextOut(back, 1280/2, 720/2+32+16, "quit", 4);
	}

	else {
		TextOut(back, 1280/2, 720/2, "play", 4);
		TextOut(back, 1280/2, 720/2+32+16, "> quit", 6);
	}

	SelectObject(back, oldFont);
	
}