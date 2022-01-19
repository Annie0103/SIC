#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <map>
//table 都用map存
//C'EOF'=>引號內有3個字元
//X'F1'=>每兩個hex為1byte=1
struct SYMTAB{
public: 
	std::string symbol;
	std::string loc;
	std::string statement;//address or 常數
	std::string space;//reserve word
	int length;//佔幾個byte
};
struct OPTAB{
	string mnemonic;
	int opcode;
};

class instruction{
	public:
		std::string label;
		std::string directitives;//START、END、BYTE、WORD、RESB、RESW
		std::string opCode;
		char n,i,x,b,p,e;
		char indirectMark="@";
		char format4Mark="+";
		char immediateMark="#";
		std::string number;
		std::string disp;
		std::string address;//for format4
		std::string loc;
		std::string objectCode;
		//std::map<string, SYMTAB> symbolTable; 放main
	private:

		
};
class type1::instruction {//RSUB 4C => 4F0000(010011 110000 0000 0000 0000 0000)

};
class type2::instruction {
	std::string statement = "";
};
class type3::instruction {//label 
	public: 
		std::string label = "";
		std::string statement = "";

		void assignSYMTAB(std::map<string, SYMTAB> symtab) {
			SYMTAB sym;
			sym.symbol = label;
			sym.statement = 
			symtab.insert(label,);

		};
};
//clear (X=B410;A=B400;S=B440;) TIXR T=B850; 
#endif