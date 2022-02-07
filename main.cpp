#include <iostream>
#include "assembler.h"
//#include "instruction.h"
#include "file.h"
#include <map>


int main(){
	//std::map<std::string, SYMTAB> symbolTable;
    file F;
    assembler A;
	F.readsource();

	A.passOne();

	A.passTwo();
	//A.outputRecord();

	system("pause");

	return 0;
}
