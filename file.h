#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include "instruction.h"
class file{//讀黨+分配type?+opcode map
	public:

		void readsource();
		void assign();
		static std::vector<std::string> insBuffer;
		static std::vector<instruction> allins;
		void writeFile(std::vector<std::string> object);
};
std::vector<std::string> file::insBuffer;
std::vector<instruction> file::allins;
#endif
