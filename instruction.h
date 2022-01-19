#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <string>
#include <vector>
#include <map>
#include "symboltable.h"
//table 都用map存
//C'EOF'=>引號內有3個字元
//X'F1'=>每兩個hex為1byte=1
/*struct SYMTAB{
	std::string symbol = "";
	std::string loc = "";
	std::string statement = "";//address or 常數
	//int length;//佔幾個byte
};*/

class instruction{
	public:
        instruction(std::string lab,std::string op, std::string sta){
			opCode = op;
			label = lab;
			statement = sta;
			//assignSYMTAB();
		}
		instruction(std::string op, std::string sta) {
			opCode = op;
			statement = sta;
		}
	    instruction(std::string op){
            opCode = op;
	    }

		std::string label="";
		std::string opCode;
		char n='1',i='1',x='0',b='0',p='1',e='0';
		std::string statement = "";
		std::string address;//for format4//4byte
		std::string loc;
		std::string objectCode;
		std::string r1 = "", r2 = "";
		int format = 3;//3byte
		void bpchange();
        void assignSYMTAB(std::map<std::string, SYMTAB> &symtab) {
                    SYMTAB sym = {"","",""};
                    sym.symbol = label;
                    markCheck();
                    sym.statement = statement;
                    symtab.insert(std::pair<std::string,SYMTAB>(label, sym));
                };
		//std::map<string, SYMTAB> symbolTable; 放main
    protected:
        void format4Check();
		void markCheck();

	private:


};

/*class type1: public instruction {//RSUB 4C => 4F0000(010011 110000 0000 0000 0000 0000)

};
class type2: public instruction {
	public:
		type2(std::string op, std::string sta) {
			opCode = op;
			statement = sta;
		}
		//std::string statement = "";
};
class type3: public instruction {//label
	public:
		type3(std::string lab,std::string op, std::string sta){
			opCode = op;
			label = lab;
			statement = sta;
			//assignSYMTAB();
		}

		/*void assignSYMTAB(std::map<std::string, SYMTAB> &symtab) {
			SYMTAB sym = {"","",""};
			sym.symbol = label;
			markCheck();
			sym.statement = statement;
			symtab.insert(std::pair<std::string,SYMTAB>(label, sym));
		};*
};*/
//clear (X=B410;A=B400;S=B440;) TIXR T=B850;

#endif
