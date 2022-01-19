#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include <map>
//table 都用map存
//C'EOF'=>引號內有3個字元
//X'F1'=>每兩個hex為1byte=1
struct SYMTAB{ 
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
		char n='1',i='1',x='0',b='0',p='1',e='0';
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
		type3(std::string op,std::string lab, std::string sta){
			opCode = op;
			label = lab;
			statement = sta;
		}
		std::string label = "";
		std::string statement = "";

		void assignSYMTAB(std::map<string, SYMTAB> symtab) {
			SYMTAB sym;
			sym.symbol = label;
			if(statement.find(",")!= std::string::npos){//若有, x=1 else =0
				x='1';
				//
				size_t pos = statement.find(",");
				statement = statement.substr(0,pos);
				sym.statement = statement;
			}
			else if(statement[0]=="#"){//immediate i=0 n=1
				i='0';n='1';
				statement.erase(0,statement.find_first_not_of("#"));
				sym.statement = statement;
			}
			else if(statement[0]=="@"){//indirect i=1 n=0
				i='1';n='0';
				statement.erase(0,statement.find_first_not_of("@"));
				sym.statement = statement;
			}
			else if(statement[0]=="C"&&statement[1]=="'"){
				std::string tmp="";
				int p=2;
				//擷取''中的東西
				//size_t found=statement.find_last_of("'");
				while(statement[p]!="'"){
					tmp+=statement[p];
				}
				statement = tmp;
				sym.statement = statement;
			}
			else if(statement[0]=="X"&&statement[1]=="'"){
				std::string tmp="";
				int p=2;				
				while(statement[p]!="'"){
					tmp+=statement[p];
				}
				statement = tmp;
				sym.statement = statement;
			}
			else
				sym.statement = statement;
			symtab.insert(label,sym);
		};
};
//clear (X=B410;A=B400;S=B440;) TIXR T=B850; 
#endif