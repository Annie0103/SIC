//sic/xe
//讀檔
//轉換
//two pass
//one pass
//寫檔
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <sstream>
using namespace std;

std::map<std::string, std::string> opMap;
string op_TAB[] = { "ADD", "ADDF", "ADDR", "AND", "CLEAR", "COMP", "COMPF", "COMPR", "DIV", "DIVF", "DIVR",
			"FIX", "FLOAT", "HIO", "J", "JEQ", "JGT", "JLT", "JSUB", "LDA", "LDB", "LDCH", "LDF", "LDL", "LDS",
			"LDT", "LDX", "LPS", "MUL", "MULF", "MULR", "NORM", "OR", "RD", "RMO", "RSUB", "SHIFTL", "SHIFTR",
			"SIO", "SSK", "STA", "STB", "STCH", "STF", "STI", "STL", "STS", "STSW", "STT", "STX", "SUB", "SUBF",
			"SUBR", "SVC", "TD", "TIO", "TIX", "TIXR", "WD" };
string opCode[] = { "18", "58", "90", "40", "B4", "28", "88", "A0", "24", "64", "9C", "C4", "C0", "F4", "3C",
			"30", "34", "38", "48", "00", "68", "50", "70", "08", "6C", "74", "04", "E0", "20", "60", "98", "C8",
			"44", "D8", "AC", "4C", "A4", "A8", "F0", "EC", "0C", "78", "54", "80", "D4", "14", "7C", "E8", "84",
			"10", "1C", "5C", "94", "B0", "E0", "F8", "2C", "B8", "DC" };
int main(){
	std::vector<std::string> intruction;
	std::vector<std::string> opcode;
	std::vector<std::string> label;
	std::vector<std::string> statement;
	
	/*std::ifstream ifs("SIC.txt",std::ios::in);
	//if(!ifs.is_open){
	//	cout<<"fail"<<endl;
	//}
	else{
		std::string tmp1/*label*,tmp2/*opcode*,tmp3/*statement*;
		while(ifs>>tmp1>>tmp2){
			cout<<
			
		}
	}*/
	/*string filename("SIC.txt");
	char* c_line = nullptr;
    size_t len = 0;

    FILE* input_file = fopen(filename.c_str(), "r");
    if (input_file == nullptr)
        return EXIT_FAILURE;

    while ((getline(&c_line, &len, input_file)) != -1) {
        lines.push_back(line.assign(c_line));
    }
	for (const auto &i : lines) {
        cout << i;
    }
    cout << endl;
    fclose(input_file);
    free(c_line);*/
	
	// Settings
    string line;
    // Open file
    ifstream myFile;
    myFile.open("SIC.txt");


	vector<intruction> allins;
    assembler assem;
	while (getline(myFile, line)) {
        cout << line << endl;
		char tmp[30];
		const char* d = "\t";
		char *p;
		int count = 0;
		vector<string> buffer;
		instrution ins;
		strcpy(tmp,line.c_str());
		p = strtok(tmp, d);
		
		while (p != NULL) {
			//printf("%s\n", p);
			/*
			std::string s = "scott>=tiger>=mushroom";
			std::string delimiter = ">=";
			
			size_t pos = 0;
			std::string token;
			while ((pos = s.find(delimiter)) != std::string::npos) {
				token = s.substr(0, pos);
				std::cout << token << std::endl;
				s.erase(0, pos + delimiter.length());
			}
			std::cout << s << std::endl;
			*/
			
			buffer.push_back(p);
			p = strtok(NULL, d);
		}
		ins = new intruction(buffer,buffer.size());
		allins.push_back(ins);
    }

    // Close file
    myFile.close();
	
	
	assembler A1;
	file F1;
	F1.readsource();
	A1.
	
    return 0;
	
}
//class initial{
void opcodemap(){
	for(int i=0;i<op_TAB.length();++i){
		opMap.insert(std::pair<std::string, std::string>(op_TAB[i], opCode[i]));
	}
}
class file{//讀黨+分配type?+opcode map
	void readsource(){
		string line;
		// Open file
		ifstream myFile;
		myFile.open("SIC.txt");

		/*vector<intruction> allins;
		assembler assem;
		while (getline(myFile, line)) {
			cout << line << endl;
			char tmp[30];
			const char* d = "\t";
			char *p;
			int count = 0;
			vector<string> buffer;
			instrution ins;
			strcpy(tmp,line.c_str());
			p = strtok(tmp, d);
			
			while (p != NULL) {				
				buffer.push_back(p);
				p = strtok(NULL, d);
			}
			ins = new intruction(buffer,buffer.size());
			allins.push_back(ins);
		}*/
		while (getline(myFile, line)) {
			//cout << line << endl;
			insBuffer.push_back(line);//one row
		}
		// Close file
		myFile.close();
		assign();
	}
	void assign(){
		//insBuffer[]
		
		for (int i = 0; i < insBuffer.size() ; ++i) {
			//cout << line << endl;
			char tmp[30];
			const char* d = "\t";
			char *p;
			int count = 0;
			vector<string> buffer;
			instrution ins;
			strcpy(tmp,line.c_str());
			p = strtok(tmp, d);
			intruction tmp ;
			
			while (p != NULL) {				
				buffer.push_back(p);
				p = strtok(NULL, d);
			}
			switch(buffer.size()){
				case 1:
					tmp = new type1();
					allins.push_back(tmp);
				break;
				case 2:
					tmp = new type2();
					allins.push_back(tmp);					
				break;
				case 3:
					tmp = new type3();
					allins.push_back(tmp);
				break;
				default:
				break;
			}
			//ins = new intruction(buffer,buffer.size());
			//allins.push_back(ins);
		}
	}
	std::vector<string> insBuffer;
	std::vector<intruction> allins;
	
};

//}
//file load into assembler save intruction(1,2,3)
//where is location at and where is object code at?
class assembler{//all//做LOCATION and object code 生成?
//存LABEL TABEL、OP TABLE pass one 
//pass two
	/*assembler(vector<string> &buf, int count){
		readfile.readource();
		
		for(vector size){
			intruction tmp ;
			std::string opcode = "";
			std::string label = "";
			std::string statement = "";
			std::int loc = 0x0000;
			if(count==1){
				//opcode = buf[0];
				tmp = new type1();
				instr.push_back(tmp); 
			}
			else if(count==2){
				//statement = buf[1];
				//opcode = buf[0];
				
				tmp = new type2();
				instr.push_back(tmp); 
			}
			else{
				tmp = new type3();
				instr.push_back(tmp); 
				
				/statement = buf[2];
				opcode = buf[1];
				label = buf[0];
				
				if(opcode[0]=='+'){//format4
					
				}
				if(statement[0]=='#'){
					
				}
				if(statement[1]=='\''){
					if(statement[0]=='C'){
						
					}
					if(statement[0]=='X'){
						
					}
				}/
			}
		}
	} */
	assembler(file F1){
		
	}
	~assembler{
		for(int i = 0; i<instr.ize();++i){
			delete instr[i];
		}
	}
	assembler(string label,string op, string sta){
		
	} 
	assembler(string op, string sta){
		
	} 
	assembler(string op){
		
	} 
	file readfile;
	std::vector<instrution> instr;
	std::string opcode = "";
	std::string label = "";
	std::string statement = "";
	std::int loc = 0x0000;
	string checkDirective(string op){
		switch(){
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
	}
	string passOne(){//memory symbol
		
	}
	string passTwo(){
		
		
	}
	/*string changeOP(string op){//op code change to number
		f
		return 0;
	}*/
};
class instrution{
	
	std::int objectCode = 0x0000;//default location
	std::string opcode = "";
	//std::string label = "";
	//std::string statement = "";
	std::int localloc = 0x0000;
	
};
class type1::intruction{
	
};
class type2::intruction{
	std::string statement = "";
};
class type3::intruction{//label 
	std::string label = "";
	std::string statement = "";
};
/*
assembler directives:
START
END
BYTE
WORD
RESB
RESW
*/



//test data
/*
COPY	START	0
FIRST	STL		RETADR
		LDB		#LENGTH
		BASE	LENGTH
CLOOP	+JSUB	RDREC
		LDA		LENGTH
		COMP	#0
		JEQ		ENDFIL
		+JSUB	WRREC
		J		CLOOP
ENDFIL	LDA		EOF
		STA		BUFFER
		LDA		#3
		STA		LENGTH
		+JSUB	WRREC
		J		@RETADR
EOF		BYTE	C'EOF'
RETADR	RESW	1
LENGTH	RESW	1
BUFFER	RESB	4096
RDREC	CLEAR	X
		CLEAR	A
		CLEAR	S
		+LDT	#4096
RLOOP	TD		INPUT
		JEQ		RLOOP
		RD		INPUT
		COMPR	A,S
		JEQ		EXIT
		STCH	BUFFER,X
		TIXR	T
		JLT		RLOOP
EXIT	STX		LENGTH
		RSUB
INPUT	BYTE	X'F1'
WRREC	CLEAR	X
		LDT		LENGTH
WLOOP	TD		OUTPUT
		JEQ		WLOOP
		LDCH	BUFFER,X
		WD		OUTPUT
		TIXR	T
		JLT		WLOOP
		RSUB
OUTPUT	BYTE	X'05'
		END		FIRST
*/