#pragma once
#include <vector>

//!
//! 2 wymiarowy wektor reprezentujacy rysunek
//! 
typedef std::vector<std::vector<bool>> Drawing;
//!
//! struktura zolwia
//! 
struct Turtle {
	int angle = 0;
	float x = 0;
	float y = 0;
};


//!
//! Funkcja zmienia pozycja zolwia i rysuje linie w miejscu przebytej drogi
//!
void moveTurtle(Turtle& turtle, Drawing& drawing, float distance);
//!
//! Funkcja zmienia kat obrotu zolwia
//!
void rotateTurtle(Turtle& turtle, int rotation);
//!
//! Funkcja rysuje linie pomiedzy dwoma punktami
//! 
//! Algorytm Bresenhama
//!
void drawLine(Drawing& drawing, int x1, int y1, int x2, int y2);
