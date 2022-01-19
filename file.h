#ifndef FILE_H
#define FILE_H

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
	
#endif