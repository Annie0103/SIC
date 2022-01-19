#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
struct SYMTAB{
	std::string symbol = "";
	std::string loc = "";
	std::string statement = "";//address or 常數
	//int length;//佔幾個byte
};
#endif
