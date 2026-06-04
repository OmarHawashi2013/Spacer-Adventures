#pragma once

int screenX = 1280;
int screenY = 720;
int cameraX = 0;
int cameraY = 0;

int gameState = 0;

float sub_x = 0, sub_y = 0;

bool canShoot = true;

float lerp(float a,float b,float t){
	return a + (b - a) * t;
}

HFONT hFont = CreateFont(
	32, // height
	0, // width
	0,
	0,
	FW_NORMAL,
	FALSE, FALSE, FALSE,
	DEFAULT_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	NONANTIALIASED_QUALITY,
	DEFAULT_PITCH | FF_SWISS,
	"Minecraft"
);

HFONT hFontMid = CreateFont(
	16 + 8, // height
	0, // width
	0,
	0,
	FW_NORMAL,
	FALSE, FALSE, FALSE,
	DEFAULT_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	NONANTIALIASED_QUALITY,
	DEFAULT_PITCH | FF_SWISS,
	"Minecraft"
);

HFONT hFontSmall = CreateFont(
	16, // height
	0, // width
	0,
	0,
	FW_NORMAL,
	FALSE, FALSE, FALSE,
	DEFAULT_CHARSET,
	OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,
	NONANTIALIASED_QUALITY,
	DEFAULT_PITCH | FF_SWISS,
	"Minecraft"
);