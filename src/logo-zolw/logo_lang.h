#pragma once
#include <string>
#include <map>
#include <vector>

#include "turtle.h"

//!
//! wektor argumentow (float)
//!
typedef std::vector<float> Arguments;
//!
//! wektor parametrow (string)
//!
typedef std::vector<std::string> Parameters;
//!
//! struktura representujaca pojedyncza komende
//!
struct Cmd {
	std::string name;
	Parameters params;
};
//!
//! wektor komand Cmd
//!
typedef std::vector<Cmd> Procedure;
//!
//! mapa procedur nazwa-procedury -> Procedure
//!
typedef std::map<std::string, Procedure> Procedures;
//!
//! struktora zawierajaca mape Procedures oraz napis bledu
//! jesli napis jest pusty - brak errora
//!
struct Code {
	Procedures procedures;
	std::string error = "";
};
//!
//! mapa uzywana do zamiany parametru na argument
//! 
typedef std::map<std::string, float> ParamsToArgs;

//!
//! Funkcja zapisuje kod z pliku w postaci mapy procedur - wektor komend
//! domyslnie zapisuje komendy do procedury main
//! podczas napotkania na nowa procedure - tworzy nowy wektor w mapie procedur o nazwie tej procedury
//! 
//! Zwraca strukture skladajaca sie z std::string error oraz mapy procedur
//!
Code loadCode(const std::string& fname);
//!
//! Funkcja zamienia linie z pliku na strukture komendy
//! 
//! Zwraca strukture Cmd
//!
Cmd strToCmd(const std::string& strCmd);

//!
//! Funkcja wykonuje program podany w wektorze prodecur
//! 
//! Tworzy strukture Turtle
//! wartosci struktury sa ustawiane na:
//! angle = 90
//! x = (rozmiar obrazka) / 2
//! y = (rozmiar obrazka) / 2
//! tak aby zolw zaczynal na srodku obrazka, obrocony do gory
//! 
//! Zwraca rysunek w postaci dwu wymiaroego wektora bool'i
//!
Drawing execProgram(const Procedures& procedures, int drawingSize);
//!
//! Funkcja wykonuje procedure
//! 
//! W petli wykonywane sa po kolei wszystkie komendy
//! 
//! Jesli napotka if - sprawdza warunek
//! gdy warunek jest falszywy - przechodzi do konca warunku
//! gdy jest prawdziwy - kontynuuje wykonywanie komend
//! 
void execProcedure(Turtle& turtle, Drawing& drawing, const Procedures& procedures, const std::string& procedureName, const Arguments& paramsToArgs);
//!
//! Funkcja wykonuje komende
//! 
//! Jezeli komenda jest przod, tyl, lewo lub prawo to wywoluje funkcje moveTurtle
//! 
//! W przeciwnym razie wywolywana jest procedura
//!
void execCmd(Turtle& turtle, Drawing& drawing, const Procedures& procedures, const ParamsToArgs& paramToArgs, const Cmd& cmd);
//!
//! Funkcja obliczajaca wyrazenie
//! obsluguje mnozenie, dodawanie i odejmowanie
//!
float variableToFloat(const ParamsToArgs& params, const std::string& var);
//!
//! Funkcja zamienia zmienna na wartosc
//!
float operationToFloat(const ParamsToArgs& params, const std::string& expr);
