#pragma once
#include <string>

#include "turtle.h"


//!
//! Funkcja tworzy bitmape przedstawiajaca rysunek
//!
void makeTXTDrawing(const Drawing& drawing, const std::string& fname);
//!
//! Funkcja tworzy plik tekstowy zawierajacy rysunek
//!
void makeBMPDrawing(const Drawing& drawing, const std::string& fname);
//!
//! Funkcja usuwa z napisu wszystko po ostatniej kropce razem z kropka
//!
std::string removeExtension(std::string fname);
