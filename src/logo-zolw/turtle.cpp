#include "turtle.h"


void moveTurtle(Turtle& turtle, Drawing& drawing, float distance) {
	float radians = turtle.angle * 3.14159265359f / 180;
	float moveX = distance * cosf(radians);
	float moveY = distance * sinf(radians);

	drawLine(drawing, lround(turtle.x), lround(turtle.y), lround(turtle.x + moveX), lround(turtle.y + moveY));

	turtle.x = turtle.x + moveX;
	turtle.y = turtle.y + moveY;
}

void rotateTurtle(Turtle& turtle, int rotation) {
	turtle.angle += rotation;
}

void drawLine(Drawing& drawing, int x1, int y1, int x2, int y2) {
	int x, y, dx, dy, p;
	int incx, incy, balance;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0)
		dx = -dx;
	if (dy < 0)
		dy = -dy;

	incx = 1;
	if (x2 < x1)
		incx = -1;
	incy = 1;
	if (y2 < y1)
		incy = -1;
	x = x1;
	y = y1;

	if (dx > dy) {
		p = 2 * dy - dx;
		balance = 2 * dy - 2 * dx;
		while (x != x2) {
			if (x >= 0 && x < drawing[0].size() && y >= 0 && y < drawing.size()) {
				drawing[y][x] = true;
			}

			if (p >= 0) {
				y += incy;
				p += balance;
			}
			else
				p += 2 * dy;

			x += incx;
		}
	}
	else {
		p = 2 * dx - dy;
		balance = 2 * dx - 2 * dy;
		while (y != y2) {
			if (x >= 0 && x < drawing[0].size() && y >= 0 && y < drawing.size()) {
				drawing[y][x] = true;
			}

			if (p >= 0) {
				x += incx;
				p += balance;
			}
			else
				p += 2 * dx;
			y += incy;
		}
	}
}
