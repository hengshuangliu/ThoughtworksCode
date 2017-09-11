#include <iostream>
#include <fstream>
#include <string>
#include "BadmintonRun.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	std::ofstream ofs;
	ofs.open ("output.txt");
	if(!ofs.is_open()){
		std::cout << "Error: openning file!" << std::endl;
	}
	BadmintonRun runer;
	runer.run(std::string(".\\badmintonManager.config"), ofs);
	ofs.close();
	system("pause");
	return 0;
}

