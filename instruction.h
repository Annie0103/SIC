#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <map>
//C'EOF'=>引號內有3個字元
//X'F1'=>每兩個hex為1byte=1
struct SYMTAB{
	string symbol;
	string loc;
	string number;
	string space;//reserve word
};
struct OPTAB{
	string mnemonic;
	int opcode;
};

class instruction{
	public:
		string label;
		string directitives;//START、END、BYTE、WORD、RESB、RESW
		string opCode;
		char n,i,x,b,p,e;
		char indirectMark="@";
		char format4Mark="+";
		char immediateMark="#";
		string number;
		string disp;
		string address;//for format4
		string objectCode;
		
		
};

#endif