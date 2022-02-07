#include "file.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "instruction.h"
#include <iterator>


std::vector<std::string> file::insBuffer;
std::vector<instruction> file::allins;
void file::readsource() {
	std::string line = "";
	// Open file
	std::ifstream myFile;
	myFile.open("SIC.txt");


	while (getline(myFile, line)) {
		insBuffer.push_back(line);//one row
	}
	// Close file
	myFile.close();
	assign();
}

void file::assign() {
	//insBuffer[]
	for (int i = 0; i < insBuffer.size(); ++i) {
        instruction *tmp1;
        std::vector<std::string> buffer;
        std::vector<std::string> words{};
        char delimiter = ' ';

        std::istringstream iss(insBuffer[i]);
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(words));

        for (const auto &str : words) {
            buffer.push_back(str);
            //std::cout << str << std::endl;
        }
        switch (buffer.size()) {
			case 1:
				tmp1 = new instruction(buffer[0]);
				allins.push_back(*tmp1);
				//std::cout<< allins[0].opCode <<"1 ";
				break;
			case 2:
				tmp1 = new instruction(buffer[0], buffer[1]);
				allins.push_back(*tmp1);
				//std::cout<< allins[0].opCode <<"2 ";
				break;
			case 3:
				tmp1 = new instruction(buffer[0], buffer[1], buffer[2]);
				allins.push_back(*tmp1);
				//std::cout<< allins[0].opCode <<"3 ";
				break;
			default:
				break;
		}
	}

	/*for (int i = 0; i < insBuffer.size(); ++i) {
		//std::cout << insBuffer[i] << std::endl;
		char tmp[100];
		const char* d = "\t";
		char* p;
		std::vector<std::string> buffer;

		std::strcpy(tmp, insBuffer[i].c_str());
		p = std::strtok(tmp, d);

        std::cout<< p <<" ";
		while (p != NULL) {
			buffer.push_back(p);
			p = strtok(NULL, d);
			std::cout<< p <<" ";
		}
		instruction *tmp1;
		std::cout<<"123123"<<" ";
		switch (buffer.size()) {
			case 1:
				tmp1 = new instruction(buffer[0]);
				allins.push_back(*tmp1);
				std::cout<< allins[0].opCode <<"1 ";
				break;
			case 2:
				tmp1 = new instruction(buffer[0], buffer[1]);
				allins.push_back(*tmp1);
				std::cout<< allins[0].opCode <<"2 ";
				break;
			case 3:
				tmp1 = new instruction(buffer[0], buffer[1], buffer[2]);
				allins.push_back(*tmp1);
				std::cout<< allins[0].opCode <<"3 ";
				break;
			default:
				break;
		}
		//ins = new intruction(buffer,buffer.size());
		//allins.push_back(ins);
	}*/
}

void file::writeFile(std::vector<std::string> object) {
	std::fstream wfile;
	wfile.open("Record.txt", std::ios::out);      //¶}±ÒÀÉ®×
	if (!wfile) {
		exit(1);
	}
	for (int i = 0; i < object.size(); ++i) {
		//¿é¥Xrecord
		wfile << object[i] << std::endl;
	}
}
