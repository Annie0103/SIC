#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <map>
#include "symboltable.h"

struct op{
    std::string mnemonic;
    std::string opcode;
    std::string format;
};
class assembler{

	public:
		void passOne();
		void passTwo();
		void outputRecord();


	private:
		int LOCCTR;//紀錄record長度
		int length;
		std::string Record;
		std::string base = "0000";
		void assignLoc();
		void hexToBinary(std::string &);
		std::string binaryToHex(std::string&);
		std::string  decimalToHex(int);
		std::string decimalToBinary(int);
		int hexToDec(std::string);
		void caculateObjCode();
		void directive();
		int stringToInt(std::string s);
		std::string intToString(int num);
		void Modify();
		std::map<std::string, op> opMap;
		void opcodemap();
        std::map<std::string, SYMTAB> symbolTable;
		std::vector<std::string> op_TAB = { "ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP", "COMPF", "COMPR", "DIV", "DIVF", "DIVR",
					"FIX", "FLOAT", "HIO", "J", "JEQ", "JGT", "JLT", "JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL", "LDS",
					"LDT", "LDX", "LPS", "MUL", "MULF", "MULR", "NORM", "OR", "RD", "RMO", "RSUB", "SHIFTL", "SHIFTR",
					"SIO", "SSK", "STA", "STB", "STCH", "STF", "STI", "STL", "STS", "STSW", "STT", "STX", "SUB", "SUBF",
					"SUBR", "SVC", "TD", "TIO", "TIX", "TIXR", "WD" };
		std::vector<std::string> opCode = { "18", "58", "90", "40", "B4", "28", "88", "A0", "24", "64", "9C", "C4", "C0", "F4", "3C",
					"30", "34", "38", "48", "00", "68", "50", "70", "08", "6C", "74", "04", "E0", "20", "60", "98", "C8",
					"44", "D8", "AC", "4C", "A4", "A8", "F0", "EC", "0C", "78", "54", "80", "D4", "14", "7C", "E8", "84",
					"10", "1C", "5C", "94", "B0", "E0", "F8", "2C", "B8", "DC" };
		std::vector<std::string> opFormat = { "3","3","2","3","2","3","3","2","3","3","2","1","1","1","3","3","3","3","3","3","3","3",
					"3","3","3","3","3","3","3","3","2","1","3","3","2","3","2","2","1","3","3","3","3","3","3","3","3","3",
					"3","3","3","3","2","2","3","1","3","2","3"	};
};

#endif
