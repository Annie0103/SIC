#include "instruction.h"
void instruction::bpchange() {
	b = '1';
	p = '0';
}
void instruction::format4Check() {//for opcode
	if (opCode.find("+") != std::string::npos) {//若有, format4
		e = '1';
		format = 4;

	}
}

void instruction::markCheck() {//for statement
	if (statement.find(",") != std::string::npos) {//若有, x=1 else =0
		size_t pos = statement.find(",");
		char tmp1 = statement[0];
		char tmp2 = statement[2];

		if ((tmp1=='X'|| tmp1 == 'A' || tmp1 == 'S' || tmp1 == 'T')&&
			(tmp2 == 'X' || tmp2 == 'A' || tmp2 == 'S' || tmp2 == 'T')) {//format2
			format = 2;//2byte
			switch (tmp1) {
				case 'A':r1 = "0";break;
				case 'X':r1 = "1";break;
				case 'L':r1 = "2";break;
				//case "PC":r1 = "8";break;
				//case "SW":r1 = "9";break;
				case 'B':r1 = "3";break;
				case 'S':r1 = "4";break;
				case 'T':r1 = "5";break;
				case 'F':r1 = "6";break;
			}
			switch (tmp2) {
				case 'A':r2 = "0"; break;
				case 'X':r2 = "1"; break;
				case 'L':r2 = "2"; break;
				//case "PC":r2 = "8"; break;
				//case "SW":r2 = "9"; break;
				case 'B':r2 = "3"; break;
				case 'S':r2 = "4"; break;
				case 'T':r2 = "5"; break;
				case 'F':r2 = "6"; break;
			}
		}
		else {
			x = '1';
			statement = statement.substr(0, pos);
		}

	}
	else if (statement[0] == '#') {//immediate i=0 n=1
		i = '0'; n = '1';
		statement.erase(0, statement.find_first_not_of("#"));
	}
	else if (statement[0] == '@') {//indirect i=1 n=0
		i = '1'; n = '0';
		statement.erase(0, statement.find_first_not_of("@"));
	}
	else if (statement[0] == 'C' && statement[1] == '\'') {
		std::string tmp = "";
		int p = 2;
		//擷取''中的東西
		while (statement[p] != '\'') {
			tmp += statement[p];
		}
		statement = tmp;
	}
	else if (statement[0] == 'X' && statement[1] == '\'') {
		std::string tmp = "";
		int p = 2;
		while (statement[p] != '\'') {
			tmp += statement[p];
		}
		statement = tmp;
	}
}
