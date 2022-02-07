#include "assembler.h"
#include "file.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

void assembler::opcodemap() {
	for (int i = 0; i < op_TAB.size(); ++i) {
        hexToBinary(opCode[i]);
        op tmp = {op_TAB[i], opCode[i],opFormat[i]};
		opMap.insert(std::pair<std::string, op>(op_TAB[i], tmp));
	}
}
void assembler::passOne(){//ok
    opcodemap();
    int o =0;
    while(o!=file::allins.size()){
        if (file::allins[o].opCode == "START") {
            file::allins[o].loc = LOCCTR;
            LOCCTR = stoi(file::allins[o].statement);//"0000"

            break;
        }
        o++;
    }
	for (int k = 0; k < file::allins.size() ; ++k) {
		//label 建好，加入loc

        if (file::allins[k].label!="") {

			file::allins[k].assignSYMTAB(symbolTable);

			symbolTable[file::allins[k].label].loc = decimalToHex(LOCCTR);

			file::allins[k].loc = decimalToHex(LOCCTR);

		}

		if (file::allins[k].opCode == "RESB") {
			file::allins[k].loc = decimalToHex(LOCCTR);
			int tnp = std::stoi(file::allins[k].statement);
			decimalToHex(tnp);

			LOCCTR += tnp ;

		}
		else if (file::allins[k].opCode == "RESW") {
			file::allins[k].loc = decimalToHex(LOCCTR);
			int tnp = std::stoi(file::allins[k].statement);
			//decimalToHex(tnp);
			tnp = tnp *3;
			LOCCTR += tnp ;

		}
		else if (file::allins[k].opCode == "BYTE") {
			file::allins[k].loc = decimalToHex(LOCCTR);

            LOCCTR += file::allins[k].litlength;

		}
		else if (file::allins[k].opCode == "WORD") {
			file::allins[k].loc = decimalToHex(LOCCTR);
			LOCCTR += 3;

		}
		else if (file::allins[k].opCode == "CLEAR") {
			file::allins[k].loc = decimalToHex(LOCCTR);
			file::allins[k].format = 2;
			LOCCTR += 2;
		}
		else if (file::allins[k].opCode == "BASE") {
			base = file::allins[k].statement;
			file::allins[k].loc = "";

		}
		else if (file::allins[k].opCode == "END") {//START、END、BYTE、WORD、RESB、RESW、CLEAR、BASE
			//LOCCTR = *1;
			file::allins[k].loc = "";
			length = LOCCTR;
		}
		else {//search optab

			auto itr = opMap.find(file::allins[k].opCode);
			if (itr != opMap.end()) {
				file::allins[k].loc = decimalToHex(LOCCTR);

				if(itr->second.format == "2"){
                     file::allins[k].format = 2;
				}

				LOCCTR += file::allins[k].format;//3;
			}
		}

	}

    /*for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); it++) {
        std::cout << "label: " << (*it).first << ", statement: " << (*it).second.loc << "\n";
    }
    std::cout<<"==================================="<<std::endl;
    for(int k = 0; k < file::allins.size() ; ++k){
        std::cout<<"loc: "<< file::allins[k].loc<<" statement: "<<file::allins[k].statement<<std::endl;
    }
    std::cout<<"==================================="<<std::endl;
    for (auto it = opMap.rbegin(); it != opMap.rend(); it++) {
        std::cout << "mnemonic: " << (*it).first << ", op: " << (*it).second.opcode << "\n";
        std::cout<<opMap[(*it).first].opcode.substr(0,6)<<std::endl;
    }*/

}



void assembler::passTwo(){
	//search optab

	char flag = '0';
	for (int h = 0; h < file::allins.size(); ++h) {
		if (file::allins[h].opCode == "START") {
			flag = '1';
			continue;
		}
		if(file::allins[h].opCode == "CLEAR"){

            std::string tmp="";
            switch(file::allins[h].statement[0]){
                case 'X':tmp = "1";break;
                case 'A':tmp = "0";break;
                case 'S':tmp = "4";break;
                case 'T':tmp = "5";break;
                case 'B':tmp = "3";break;
				case 'F':tmp = "6";break;
				case 'L':tmp = "2";break;

            }
            file::allins[h].objectCode = "B4" + tmp +"0";
		}
		else if (flag == '1') {

			auto itr = opMap.find(file::allins[h].opCode);
			if (itr != opMap.end()) {

				//make obj code
				if (file::allins[h].format == 1||itr->second.format == "1") {//format 1
				//op = 8
					file::allins[h].objectCode = opMap[file::allins[h].opCode].opcode;//file::allins[h].opCode;
				}
				else if (file::allins[h].format == 2||itr->second.format == "2") {//format 2
				//op = 8; r1 = 4; r2 = 4
                    if(file::allins[h].opCode=="TIXR"){
                        std::string tmp="";
                        switch(file::allins[h].statement[0]){
                            case 'X':tmp = "1";break;
                            case 'A':tmp = "0";break;
                            case 'S':tmp = "4";break;
                            case 'T':tmp = "5";break;
                            case 'B':tmp = "3";break;
                            case 'F':tmp = "6";break;
                            case 'L':tmp = "2";break;

                        }
                        file::allins[h].objectCode = "B8" + tmp + "0";
                    }
                    else{
                        file::allins[h].objectCode =
                        opMap[file::allins[h].opCode].opcode + file::allins[h].r1 + file::allins[h].r2;
                    }
				}

				else if (file::allins[h].format == 3 && itr->second.format == "3") {//format 3
				//op = 6; nixbpe = 6; disp = 12(TA = PC + disp)

					int disp = 0;

					std::string TA = file::allins[h].statement;//可能是數字 OR label

					std::string DISP = "";

                    if(file::allins[h].opCode=="RSUB"){
                        file::allins[h].objectCode="4F0000";
                    }
                    else{
                        bool isnumber = true;
                        for (char const &c : TA) {
                            if (std::isdigit(c) == 0) {
                                //not number
                                int n=1;
                                while(file::allins[h + n].loc==""){
                                    ++n;
                                }
                                disp = hexToDec(symbolTable[TA].loc) - hexToDec(file::allins[h + n].loc);
                                isnumber = false;
                            }
                        }
                        if(isnumber){
                            disp = stoi(TA);
                        }

                        if (disp > 2047 && disp < -2048) { // 超過pc 可容忍範圍，B

                            disp = hexToDec(symbolTable[TA].loc) - hexToDec(symbolTable[base].loc);

                            file::allins[h].bpchange();


                        }
                        DISP = decimalToBinary(disp);
                        for (int i = 0; DISP.length() < 12; ++i) {
                                DISP = "0" + DISP;
                        }

                        file::allins[h].objectCode = opMap[file::allins[h].opCode].opcode.substr(0,6) + file::allins[h].n +
                         file::allins[h].i + file::allins[h].x + file::allins[h].b + file::allins[h].p + file::allins[h].e + DISP;
                        std::string obj = binaryToHex(file::allins[h].objectCode);
                        file::allins[h].objectCode=obj;
                    }
				}
				else {//format 4
				//op = 6; nixbpe = 6; address = 20
					std::string address= file::allins[h].statement;//可能是數字也可能是label
					//run symtab 存在=label、不存在 = 數字
					auto itr = symbolTable.find(address);
					if ( itr != symbolTable.end()) {
						//存在
						address = itr->second.loc;
						for (int i = 0; address.length() < 5; ++i) {
							address = "0" + address;
						}
						file::allins[h].objectCode = opMap[file::allins[h].opCode].opcode.substr(0, 6) +
                        file::allins[h].n + file::allins[h].i + file::allins[h].x + file::allins[h].b +
                        file::allins[h].p + file::allins[h].e; /*+ address;*/
                        std::string obj = binaryToHex(file::allins[h].objectCode);
                        obj+=address;
                        file::allins[h].objectCode=obj;
					}
					else {
						//number， to binary
						int tmp = stoi(address);
						address = decimalToBinary(tmp);
						for (int i = 0; address.length() < 20; ++i) {
							address = "0" + address;
						}//?
						file::allins[h].objectCode = opMap[file::allins[h].opCode].opcode.substr(0, 6) +
                        file::allins[h].n + file::allins[h].i + file::allins[h].x + file::allins[h].b +
                        file::allins[h].p + file::allins[h].e + address;
                        std::string obj = binaryToHex(file::allins[h].objectCode);
                        file::allins[h].objectCode=obj;
					}


				}
			}

			if(file::allins[h].opCode == "BYTE"){
                if(file::allins[h].statement == "EOF"){
                    file::allins[h].objectCode="454F46";
                }
                else{
                    file::allins[h].objectCode=file::allins[h].statement;
                }

			}
			else if(file::allins[h].opCode == "WORD"){//WORD

			}

		}
	}

    for(int k = 0; k < file::allins.size() ; ++k){
        std::cout<<"loc: "<< file::allins[k].loc<<" obj: "<<file::allins[k].objectCode<<std::endl;
    }
}



void assembler::outputRecord(){
	int i = 0;
	for (i = 0; i < file::allins.size(); ++i) {
            if(file::allins[i].opCode=="START"){
                Record = "H" + file::allins[i].label;
                for (int i = 0; file::allins[i].statement.length() < 6; ++i) {
							file::allins[i].statement = "0" + file::allins[i].statement;
                }
                Record = Record + file::allins[i].statement + decimalToHex(length) + "\n";
                break;
            }


		std::cout << file::allins[i].objectCode << " ";
	}
	std::string tmpr = "";
	std::string firstloc = "";
	for (int x = i; x < file::allins.size(); ++x) {


        if(file::allins[i].opCode.substr(0,3) == "RES"){

                for (int i = 0; file::allins[i].loc.length() < 6; ++i) {
                    file::allins[i].loc = "0" + file::allins[i].loc;
                }
                Record = "T"+ file::allins[x].loc+file::allins[x].objectCode ;
                firstloc = file::allins[x].loc ;

        }

        int iii = tmpr.length();
        int ppp = file::allins[x].objectCode.length();
        iii += ppp;
        if(iii >59){
            std::string tmp = decimalToHex(hexToDec(file::allins[x].loc)-hexToDec(firstloc));
            Record = Record + tmp + tmpr + "/n";
            for (int i = 0; file::allins[i].loc.length() < 6; ++i) {
                    file::allins[i].loc = "0" + file::allins[i].loc;
            }
            Record = "T"+ file::allins[x].loc+file::allins[x].objectCode;
            firstloc = file::allins[x].loc ;
            tmpr = "";
        }
        else{
            tmpr = tmpr + file::allins[x].objectCode;
        }
        //Record = Record + file::allins[x].objectCode;

	}
	Modify();
	std::cout<<Record;
}

void assembler::Modify() {//relocation
    std::string tmp;
    for (int h = 0; h < file::allins.size(); ++h) {
        if(file::allins[h].format == 4){
            tmp =  decimalToHex(hexToDec(file::allins[h].loc)+1);
            for (int i = 0; tmp.length() < 6; ++i) {
                tmp= "0" + tmp;
            }

            Record = "M"+tmp +"05"+"\n";
        }


    }

}
int assembler::hexToDec(std::string hexVal)
{
    int number;
	number = stoi(hexVal, 0, 16);

	return number;
}
std::string  assembler::decimalToHex(int decimal) {

    char hex[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    std::string hexdec_num="";
    int r;
    if(decimal==0){
        hexdec_num="0000";
    }
    while(decimal>0)
    {
        r = decimal % 16;
        hexdec_num = hex[r] + hexdec_num;
        decimal = decimal/16;
    }
    for (int i = 0; hexdec_num.length() < 4; ++i) {
		hexdec_num = "0" + hexdec_num;
	}


    return hexdec_num;
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
