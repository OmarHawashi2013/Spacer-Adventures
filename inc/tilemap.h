#pragma once

class Map
{
public:
	unsigned char m[256][256] = {}; // map

	int mapW;
	int mapH;

	HBITMAP _1;
	HBITMAP _2;
	HBITMAP _3;

	HDC dc;

	std::ifstream l_file; // level file



	Map(int MW, int MH) {
		mapW = MW;
		mapH = MH;
	};

	void init(HDC hdc, LPCSTR _1_Path, LPCSTR _2_Path, LPCSTR _3_Path, const char* _l_path){
		dc = CreateCompatibleDC(hdc);

		_1 = (HBITMAP) LoadImageA(
			NULL,
			_1_Path,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE
		);

		_2 = (HBITMAP) LoadImageA(
			NULL,
			_2_Path,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE
		);

		_3 = (HBITMAP) LoadImageA(
			NULL,
			_3_Path,
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE
		);

		l_file.open(_l_path);

		for (int y = 0; y < mapH; ++y){
			for (int x = 0; x < mapW; ++x){
				l_file >> m[y][x];
			}
		}

		l_file.close();
	}

	void render(HDC back){
		for (int y = 0; y < mapH; ++y){
			for (int x = 0; x < mapW; ++x){
				if (m[y][x] == '1') {
					SelectObject(dc, _1);
					TransparentBlt(
						back,
					    (x * 64) - sub_x, (y * 64) - sub_y, 64, 64,
					 	dc,
						0, 0, 64, 64,
						RGB(100, 100, 100)
					);

					if (ShowCollisions) {
						RECT r = {(int)(x * 64 - sub_x), (int)(y * 64 - sub_y), (int)(x*64+64 - sub_x), (int)(y*64+64 - sub_y)};
						FrameRect(back, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
					}
				}



				else if (m[y][x] == '2') {
					SelectObject(dc, _2);
					TransparentBlt(
						back,
					    (x * 64) - sub_x, (y * 64) - sub_y, 64, 64,
					 	dc,
						0, 0, 64, 64,
						RGB(100, 100, 100)
					);

					if (ShowCollisions) {
						RECT r = {(int)(x * 64 - sub_x), (int)(y * 64 - sub_y), (int)(x*64+64 - sub_x), (int)(y*64+64 - sub_y)};
						FrameRect(back, &r, (HBRUSH)GetStockObject(WHITE_BRUSH));
					}
				}

				else if (m[y][x] == '0') {
					SelectObject(dc, _3);
					TransparentBlt(
						back,
					    (x * 64) - sub_x, (y * 64) - sub_y, 64, 64,
					 	dc,
						0, 0, 64, 64,
						RGB(100, 100, 100)
					);
				}
			}		
		}
	}
	void del(){
		DeleteObject(_1);
		DeleteObject(_2);
		DeleteObject(_3);
		DeleteDC(dc);
	}
	
};