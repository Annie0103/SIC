#include "assembler.h"

/*

	public: 
		void passOne();
		void passTwo();
		void outputRecord();
	
	private:
		int LOCCTR;//紀錄record長度、
		void assignLoc();
		void hexToBinary();
		void binaryToHex();
		void caculateObjCode();

*/

void assembler::passOne(){
	
}
void assembler::passTwo(){
	
}
void assembler::outputRecord(){
	
}
void assembler::assignLoc(){
	
}
void assembler::hexToBinary(std::string &hex){
	
	for(int i=0;i<hex.length();++i){
		switch(hex[i])
		{
			case '0':
				hex[i]="0000";
				break;
			case '1':
				hex[i]="0001";
				break;
			case '2':
				hex[i]="0010";
				break;
			case '3':
				hex[i]="0011";
				break;
			case '4':
				hex[i]="0100";
				break;
			case '5':
				hex[i]="0101";
				break;
			case '6':
				hex[i]="0110";
				break;
			case '7':
				hex[i]="0111";
				break;
			case '8':
				hex[i]="1000";
				break;
			case '9':
				hex[i]="1001";
				break;
			case 'A':
			case 'a':
				hex[i]="1010";
				break;
			case 'B':
			case 'b':
				hex[i]="1011";
				break;
			case 'C':
			case 'c':
				hex[i]="1100";
				break;
			case 'D':
			case 'd':
				hex[i]="1101";
				break;
			case 'E':
			case 'e':
				hex[i]="1110";
				break;
			case 'F':
			case 'f':
				hex[i]="1111";
				break;
			default:
				//hex[i]=--Invalid Hex Digit ("<<hexDecNum[i]<<")--";
		}
	}
}
void assembler::binaryToHex(){
	
}
void assembler::caculateObjCode(){
	
}
