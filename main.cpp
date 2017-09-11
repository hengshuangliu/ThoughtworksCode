#include <iostream>
#include <string>
#include "BadmintonRun.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int main(int argc, char** argv) {
	BadmintonRun runer;
	runer.run(std::string(".\\badmintonManager.config") );
	system("pause");
	return 0;
}

