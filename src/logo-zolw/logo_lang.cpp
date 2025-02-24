#include "logo_lang.h"
#include <fstream>
#include <sstream>


Code loadCode(const std::string& fname) {
	std::ifstream file(fname);

	Procedures procedures;
	std::string error;
	
	if (!file.is_open()) {
		return Code{ procedures, "Nie mozna otworzyc pliku!"};
	}

	//set main to have no params
	Cmd mainParams;
	mainParams.name = "main";
	mainParams.params = Parameters{};
	procedures["main"].push_back(mainParams);

	std::string procedureName = "main";
	std::string line;
	int line_num = 1;
	while (std::getline(file, line)) {
		auto start = line.find_first_not_of(" \n\t");
		if (start == std::string::npos) continue;
		line = line.substr(start);

		if (line.substr(0, 4) != "end ") {
			std::string newLine;
			for (auto& ch : line) {
				if (!std::isspace(ch))
					newLine += ch;
			}
			line = newLine;
		}

		if (line.back() == ';') {
			if (line == std::string("end " + procedureName + ";")) {
				//back to main if end of procedure
				procedureName = "main";
			}
			else {
				//normal command
				Cmd cmd = strToCmd(line);

				if (cmd.name != "przod" &&
					cmd.name != "tyl" &&
					cmd.name != "lewo" &&
					cmd.name != "prawo" &&
					cmd.name != "end if;"
				) {
					if (procedures.count(cmd.name) == 0) {
						return Code{ procedures, "Blad w linii: " + std::to_string(line_num) };
					}
				}

				procedures[procedureName].push_back(cmd);
			}
		}
		else if (line.substr(0, 3) == std::string("if(")) {
			//if command
			Cmd cmd = strToCmd(line);
			procedures[procedureName].push_back(cmd);
		}
		else {
			//new procedure
			auto nameEnd = line.find('(');
			if (nameEnd == std::string::npos) {
				return Code{ procedures, "Blad w linii: " + std::to_string(line_num) };
			}

			procedureName = line.substr(0, nameEnd);
			
			//set fn params as 1st cmd of procedure
			Cmd cmd = strToCmd(line);
			procedures[procedureName].push_back(cmd);
		}
		line_num++;
	}

	return Code{ procedures, "" };
}

Cmd strToCmd(const std::string& strCmd) {
	Cmd cmd;

	size_t nameEnd = strCmd.find("(");
	cmd.name = strCmd.substr(0, nameEnd);

	size_t paramsEnd = strCmd.find(")");
	std::string strParams = strCmd.substr(nameEnd + 1, paramsEnd - nameEnd - 1);
	Parameters params;

	size_t argStart = 0;
	size_t argEnd;
	while ((argEnd = strParams.find(',', argStart)) != std::string::npos) {
		params.push_back(strParams.substr(argStart, argEnd - argStart));

		argStart = argEnd + 1;
	}
	params.push_back(strParams.substr(argStart));
	
	cmd.params = params;

	return cmd;
}


Drawing execProgram(const Procedures& procedures, int drawingSize) {
	Drawing drawing;
	drawing.resize(drawingSize, std::vector<bool>(drawingSize, false));

	Turtle turtle;
	turtle.angle = 90;
	turtle.x = drawingSize / 2.f;
	turtle.y = drawingSize / 2.f;

	execProcedure(turtle, drawing, procedures, "main", Arguments{});

	return drawing;
}

void execProcedure(Turtle& turtle, Drawing& drawing, const Procedures& procedures, const std::string& procedureName, const Arguments& arguments) {
	const Procedure procedure = procedures.at(procedureName);
	
	//mapping parameters to arguments
	ParamsToArgs paramsToArgs;
	Parameters parameters = procedure[0].params;
	for (size_t i = 0; i < parameters.size(); i++) {
		paramsToArgs[parameters[i]] = arguments[i];
	}

	int ifSkiping = 0;
	
	for (size_t i = 1; i < procedure.size(); i++) {
		Cmd cmd = procedure[i];
		
		if (ifSkiping) {
			if (cmd.name == "if")
				ifSkiping++;
			else if (cmd.name == "end if;")
				ifSkiping--;
		}
		else {
			if (cmd.name == "end if;")
				continue;

			if (cmd.name == "if") { //IFCMD CHECKING
				std::string expression = cmd.params[0];

				size_t argOperatorId = expression.find("<>");
				char argOperator = '!';
				if (argOperatorId == std::string::npos) {
					argOperatorId = expression.find('>');
					argOperator = '>';
				}
				if (argOperatorId == std::string::npos) {
					argOperatorId = expression.find('<');
					argOperator = '<';
				}
				if (argOperatorId == std::string::npos) {
					argOperatorId = expression.find('=');
					argOperator = '=';
				}

				std::string strVal1 = expression.substr(0, argOperatorId);
				float val1 = operationToFloat(paramsToArgs, strVal1);
				std::string strVal2 = expression.substr(argOperatorId + 1);
				float val2 = operationToFloat(paramsToArgs, strVal2);

				switch (argOperator) {
				case '!':
					if (!(val1 != val2)) ifSkiping++;
					break;
				case '>':
					if (!(val1 > val2)) ifSkiping++;
					break;
				case '<':
					if (!(val1 < val2)) ifSkiping++;
					break;
				case '=':
					if (!(val1 == val2)) ifSkiping++;
					break;
				default:
					break;
				}
			}
			else { //NORMAL COMMAND
				execCmd(turtle, drawing, procedures, paramsToArgs, cmd);
			}
		}
	}
}

void execCmd(Turtle& turtle, Drawing& drawing, const Procedures& procedures, const ParamsToArgs& paramsToArgs, const Cmd& cmd) {
	Arguments args;
	for (size_t i = 0; i < cmd.params.size(); i++) {
		float value = operationToFloat(paramsToArgs, cmd.params[i]);
		args.push_back(value);
	}

	if (cmd.name == "przod") {
		args[0] = args[0] - 1;
		moveTurtle(turtle, drawing, args[0]);
	}
	else if (cmd.name == "tyl") {
		args[0] = args[0] - 1;
		moveTurtle(turtle, drawing, -args[0]);
	} 
	else if (cmd.name == "lewo") {
		rotateTurtle(turtle, (int)args[0]);
	}
	else if (cmd.name == "prawo") {
		rotateTurtle(turtle, (int)-args[0]);
	}
	else {
		//not default cmd - execute procedure
		execProcedure(turtle, drawing, procedures, cmd.name, args);
	}
}

float operationToFloat(const ParamsToArgs& paramsToArgs, const std::string& expr) {
	size_t operatorId = expr.find('*');
	char operatorChar = '*';
	if (operatorId == std::string::npos) {
		operatorId = expr.find('+');
		operatorChar = '+';
	}
	if (operatorId == std::string::npos) {
		operatorId = expr.find('-');
		operatorChar = '-';
	}
	if (operatorId == std::string::npos)
		return variableToFloat(paramsToArgs, expr);

	std::string strVal1 = expr.substr(0, operatorId);
	float val1 = variableToFloat(paramsToArgs, strVal1);
	std::string strVal2 = expr.substr(operatorId + 1);
	float val2 = variableToFloat(paramsToArgs, strVal2);

	switch (operatorChar) {
	case '*':
		return val1 * val2;
		break;
	case '+':
		return val1 + val2;
		break;
	case '-':
		return val1 - val2;
		break;
	default:
		//ERROR
		return 0;
		break;
	}
}

float variableToFloat(const ParamsToArgs& paramsToArgs, const std::string& var) {
	std::istringstream stream(var);

	float result;
	if (!(stream >> result)) {
		result = paramsToArgs.at(var);
	}

	return result;
}
