#include "file.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include "instruction.h"

void file::readsource() {
	std::string line = "";
	// Open file
	std::ifstream myFile;
	myFile.open("SIC.txt");


	while (getline(myFile, line)) {
		//cout << line << endl;
		insBuffer.push_back(line);//one row
	}
	// Close file
	myFile.close();
	assign();
}

void file::assign() {
	//insBuffer[]

	for (int i = 0; i < insBuffer.size(); ++i) {
		//cout << line << endl;
		std::string line;
		char tmp[30];
		const char* d = "\t";
		char* p;
		int count = 0;
		std::vector<std::string> buffer;

		std::strcpy(tmp, line.c_str());
		p = std::strtok(tmp, d);
		instruction *tmp1;

		while (p != NULL) {
			buffer.push_back(p);
			p = strtok(NULL, d);
		}
		switch (buffer.size()) {
			case 1:
				tmp1 = new instruction(buffer[0]);
				allins.push_back(*tmp1);
				break;
			case 2:
				tmp1 = new instruction(buffer[0], buffer[1]);
				allins.push_back(*tmp1);
				break;
			case 3:
				tmp1 = new instruction(buffer[0], buffer[1], buffer[2]);
				allins.push_back(*tmp1);
				break;
			default:
				break;
		}
		//ins = new intruction(buffer,buffer.size());
		//allins.push_back(ins);
	}
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
