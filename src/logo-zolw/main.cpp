#include <iostream>
#include "args_parser.h"
#include "logo_lang.h"
#include "output.h"


//!
//! Glowna funkcja programu
//!
int main(int argc, char* argv[]) {
	Args args = parseArgs(argc, argv);
	if (args == Args{}) return 1;


	Code code = loadCode(args["-i"]);
	if (code.error != "") {
		std::cout << code.error;
		return 1;
	}

	Drawing drawingArray = execProgram(code.procedures, stoi(args["-s"]));


	makeTXTDrawing(drawingArray, args["-o"]);
	makeBMPDrawing(drawingArray, args["-o"]);

	std::cout << "Program wykonany";

	return 0;
}
