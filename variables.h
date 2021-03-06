#pragma once

typedef struct _offset
{
	SkScalar w;
	SkScalar h;
	SkScalar x;
	SkScalar y;
} Offset;

static struct RGBA {
	Uint32 rmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00;
	Uint32 bmask = 0x000000ff;
	Uint32 amask = 0xff000000;
}RGBA;

static struct RGBTable {
	const int black[3] = { 0x00, 0x00, 0x00 };
	const int white[3] = { 0xFF, 0xFF, 0xFF };
	const int red[3] = { 0xFF, 0x00, 0x00 };
	const int lime[3] = { 0x00, 0xFF, 0x00 };
	const int blue[3] = { 0x00, 0x00, 0xFF };
	const int yellow[3] = { 0xFF, 0xFF, 0x00 };
	const int aqua[3] = { 0x00, 0xFF, 0xFF };
	const int magenta[3] = { 0xFF, 0x00, 0xFF };
	const int silver[3] = { 0xC0, 0xC0, 0xC0 };
	const int gray[3] = { 0x80, 0x80, 0x80 };
	const int maroon[3] = { 0x80, 0x00, 0x00 };
	const int olive[3] = { 0x80, 0x80, 0x00 };
	const int green[3] = { 0x00, 0x80, 0x00 };
	const int purple[3] = { 0x80, 0x00, 0x80 };
	const int teal[3] = { 0x80, 0x80, 0x80 };
	const int navy[3] = { 0x00, 0x00, 0x80 };
} RGBTable;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
