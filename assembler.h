#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <vector>
#include <map>

class assembler{
	
	public: 
		void passOne();
		void passTwo();
		void outputRecord();
	
	private:
		int LOCCTR;//紀錄record長度、
		void assignLoc();
		void hexToBinary(std::string &);
		void binaryToHex();
		void caculateObjCode();
	
};

#endif
