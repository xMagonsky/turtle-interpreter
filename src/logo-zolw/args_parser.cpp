#include "args_parser.h"
#include <iostream>

void printArgsUsage() {
	std::cout
		<< "Instrukcja uzywania programu: \n"
		<< " Program przyjmuje nastepujace parametry: \n"
		<< "  -i wejsciowy plik z kodem w jezyku Logo \n"
		<< "  -o wyjsciowy plik z uzyskana droga zolwia \n"
		<< "  -s rozmiar planszy \n"
		<< " Przyklad uzycia: \n"
		<< "  logo-zlow.exe -i input.txt -o output.txt -s 100 \n";
}

Args parseArgs(int argc, char* argv[]) {
	Args arguments;
	
	if (argc < 7) {
		printArgsUsage();
		return arguments;
	}

	for (size_t i = 1; i < argc; i += 2) {
		if (argv[i][0] != '-') {
			std::cout << "Parametr (" << argv[i] << ") powinien rozpoczynac sie od \"-\" \n\n";
			printArgsUsage();
			break;
		}

		if (argc <= i + 1) {
			std::cout << "Nie podano wartosci parametru (" << argv[i] << ") \n\n";
			printArgsUsage();
			break;
		}

		if (argv[i] == std::string("-i") ||
			argv[i] == std::string("-o") ||
			argv[i] == std::string("-s")
		) {
			arguments.insert(
				std::pair<std::string, std::string>(argv[i], argv[i + 1])
			);
		}
		else {
			std::cout << "Nie ma takiego argumentu jak \"" << argv[i] << "\" \n\n";
			printArgsUsage();
			break;
		}
	}

	return arguments;
}
