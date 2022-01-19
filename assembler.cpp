#include "assembler.h"
#include "file.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

void assembler::opcodemap() {
	for (int i = 0; i < op_TAB.size(); ++i) {
        hexToBinary(opCode[i]);
		opMap.insert(std::pair<std::string, std::string>(op_TAB[i], opCode[i]));
	}
}
void assembler::passOne(){

	for (int k = 0; k < file::allins.size() ; ++k) {/*while(file::allins[i].opcode!="END")*/

		//label 建好，加入loc
		if (file::allins[k].label!="") {
			file::allins[k].assignSYMTAB(symbolTable);
			symbolTable[file::allins[k].label].loc = LOCCTR;
			file::allins[k].loc = LOCCTR;
		}
		if (file::allins[k].opCode == "START") {
			file::allins[k].loc = LOCCTR;
			LOCCTR = stoi(file::allins[k].statement);//"0000"
		}
		else if (file::allins[k].opCode == "RESB") {
			file::allins[k].loc = LOCCTR;
			int tnp = std::stoi(file::allins[k].statement);
			decimalToHex(tnp);

			LOCCTR += tnp * 1;

		}
		else if (file::allins[k].opCode == "RESW") {
			file::allins[k].loc = LOCCTR;
			int tnp = std::stoi(file::allins[k].statement);
			decimalToHex(tnp);
			LOCCTR += /*decimalToHex(std::stoi(file::allins[k].statement))*/tnp *3;
		}
		else if (file::allins[k].opCode == "BYTE") {
			file::allins[k].loc = LOCCTR;
			LOCCTR += 1;

		}
		else if (file::allins[k].opCode == "WORD") {
			file::allins[k].loc = LOCCTR;
			LOCCTR += 3;

		}
		else if (file::allins[k].opCode == "CLEAR") {
			file::allins[k].loc = LOCCTR;
			LOCCTR += 2;
		}
		else if (file::allins[k].opCode == "BASE") {
			base = file::allins[k].statement;
			file::allins[k].loc = LOCCTR;
			LOCCTR += 2;
		}
		else if (file::allins[k].opCode == "END") {//START、END、BYTE、WORD、RESB、RESW、CLEAR、BASE
			//LOCCTR = *1;
			file::allins[k].loc = "";
			length = LOCCTR;
		}
		else {//search optab
			auto itr = opMap.find(file::allins[k].opCode);
			if (itr != opMap.end()) {
				file::allins[k].loc = LOCCTR;
				LOCCTR += file::allins[k].format;//3;
			}
		}

	}
}
void assembler::passTwo(){
	//search optab
	char flag = '0';
	for (int i = 0; i < file::allins.size(); ++i) {
		if (file::allins[i].opCode == "START") {
			flag = '1';
		}
		if (flag == '1') {
			for (auto itr = opMap.find(file::allins[i].opCode); itr != opMap.end(); ++itr) {
				//make obj code
				if (file::allins[i].format == 1) {//format 1
				//op = 8
					file::allins[i].objectCode = file::allins[i].opCode;
				}
				else if (file::allins[i].format == 2) {//format 2
				//op = 8; r1 = 4; r2 = 4
					file::allins[i].objectCode = file::allins[i].opCode + file::allins[i].r1 + file::allins[i].r2;
				}
				else if (file::allins[i].format == 3) {//format 3
				//op = 6; nixbpe = 6; disp = 12(TA = PC + disp)
					int disp = 0;
					std::string TA = file::allins[i].statement;
					std::string DISP = "";
					disp = std::stoi(symbolTable[TA].loc) - std::stoi(file::allins[i + 1].loc);//TODO 轉成數字//pc
					if (disp > 2047 && disp < -2048) { // 超過pc 可容忍範圍，B
						disp = std::stoi(symbolTable[TA].loc) - std::stoi(symbolTable[base].loc);

						file::allins[i].bpchange();

						DISP = decimalToBinary(disp);
						for (int i = 0; DISP.length() < 12; ++i) {
							DISP = "0" + DISP;
						}//?
					}

					file::allins[i].objectCode = file::allins[i].opCode.substr(0,6) + file::allins[i].n +
					 file::allins[i].i + file::allins[i].x + file::allins[i].b + file::allins[i].p + file::allins[i].e + DISP;
					binaryToHex(file::allins[i].objectCode);
				}
				else {//format 4
				//op = 6; nixbpe = 6; address = 20
					std::string address= file::allins[i].statement;//可能是數字也可能是label
					//run symtab 存在=label、不存在 = 數字
					auto itr = symbolTable.find(address);
					if ( itr != symbolTable.end()) {
						//存在
						address = itr->second.loc;
					}
					else {
						//number， to binary
						int tmp = stoi(address);
						address = decimalToBinary(tmp);
						for (int i = 0; address.length() < 20; ++i) {
							address = "0" + address;
						}//?
					}

					file::allins[i].objectCode = file::allins[i].opCode.substr(0, 6) +
					file::allins[i].n + file::allins[i].i + file::allins[i].x + file::allins[i].b +
					file::allins[i].p + file::allins[i].e + address;
					binaryToHex(file::allins[i].objectCode);
				}
			}

		}
	}
}
void assembler::outputRecord(){
	for (int i = 0; i < file::allins.size(); ++i) {
		std::cout << file::allins[i].objectCode << " ";
	}
}
void assembler::assignLoc(){

}
/*void assembler::directive(std::string) {
	switch (directitives) {
		case "START":
			loc = statement;//放 global
			break;
		case "END":

			break;
		case "BYTE":

			break;
		case "WORD":

			break;
		case "RESB":

			break;
		case "RESW":

			break;
		default://非directive

			break;
	}
}*/
/*void assembler::caculateObjCode(char bp){
	if (bp == 'p') {
		//TA = PC + disp

	}
	else if (bp=='b') {
		//TA = B + disp

	}
}*/
void assembler::Modify() {//relocation


}
void assembler::decimalToHex(int& decimal) {
	std::stringstream ss;
	ss << std::hex << decimal; // int decimal_value
	std::string res(ss.str());
	decimal = std::stoi(res);
	//return
	//std::cout << res;

}


void assembler::hexToBinary(std::string &hex){
    std::string tmp="";
    std::string result="";
	for(int i=0;i<hex.length();++i){
		switch(hex[i])
		{
			case '0':
				tmp="0000";
				break;
			case '1':
				tmp="0001";
				break;
			case '2':
				tmp="0010";
				break;
			case '3':
				tmp="0011";
				break;
			case '4':
				tmp="0100";
				break;
			case '5':
				tmp="0101";
				break;
			case '6':
				tmp="0110";
				break;
			case '7':
				tmp="0111";
				break;
			case '8':
				tmp="1000";
				break;
			case '9':
				tmp="1001";
				break;
			case 'A':
			case 'a':
				tmp="1010";
				break;
			case 'B':
			case 'b':
				tmp="1011";
				break;
			case 'C':
			case 'c':
				tmp="1100";
				break;
			case 'D':
			case 'd':
				tmp="1101";
				break;
			case 'E':
			case 'e':
				tmp="1110";
				break;
			case 'F':
			case 'f':
				tmp="1111";
				break;
			default:
			    break;
		}
		result += tmp;
	}
	hex= result;
}
std::string assembler::decimalToBinary(int d)
{
	std::string r;
	while (d != 0) {
		r += (d % 2 == 0 ? "0" : "1");
		d /= 2;
	}
	return r;
}
std::string assembler::binaryToHex(std::string &s){
	unsigned int i;
	unsigned int size = s.size() / 4;
	unsigned int mod = s.size() % 4;
	unsigned int xx = 4 - mod;
	std::string str = "";
	if (mod != 0) {
		for (i = 0; i < xx; i++) {
			s.insert(0, "0");
		}
		size++;
	}

	int j = 0;
	for (i = 0; i < size; i++) {
		std::string re = "";
		int p = 4;
		while (p--) {
			re.push_back(s[j++]);
		}
		if (re == "0000") {
			str += "0";
		}
		else if (re == "0001") {
			str += "1";
		}
		else if (re == "0010") {
			str += "2";
		}
		else if (re == "0011") {
			str += "3";
		}
		else if (re == "0100") {
			str += "4";
		}
		else if (re == "0101") {
			str += "5";
		}
		else if (re == "0110") {
			str += "6";
		}
		else if (re == "0111") {
			str += "7";
		}
		else if (re == "1000") {
			str += "8";
		}
		else if (re == "1001") {
			str += "9";
		}
		else if (re == "1010") {
			str += "A";
		}
		else if (re == "1011") {
			str += "B";
		}
		else if (re == "1100") {
			str += "C";
		}
		else if (re == "1101") {
			str += "D";
		}
		else if (re == "1110") {
			str += "E";
		}
		else if (re == "1111") {
			str += "F";
		}
	}
	return str;

}
int assembler::stringToInt(std::string s) {
	std::stringstream ss;
	int number = 0;
	ss << s;
	ss >> number;

	return number;
}
std::string assembler::intToString(int num) {
	std::stringstream ss;
	ss << num;

	return ss.str();
}
