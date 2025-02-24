#pragma once
#include <map>
#include <string>

//!
//! Mapa argumentow nazwa -> argument
//!
typedef std::map<std::string, std::string> Args;

//!
//! Funkcja wypisujaca instrukcje uzywania programu
//!
void printArgsUsage();
//!
//! Funkcja zamieniajaca argumenty podane przez uzytkownika na mape
//! 
//! Przyjmuje ilosc argumentow oraz tablice argumentow
//! 
//! Zwraca mape w postaci <argument><wartosc>
//!
Args parseArgs(int argc, char* argv[]);
