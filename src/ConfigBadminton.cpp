#include "ConfigBadminton.h"
#include <cstdlib>
#include <iostream>

ConfigBadminton::ConfigBadminton(std::string fileName):ConfigTool(fileName){
}

ConfigBadminton::~ConfigBadminton(){
}


std::string ConfigBadminton::getFields(){
	std::map<std::string, std::string> strings = getStrings();
	std::map<std::string, std::string>::iterator it;
	it = strings.find(std::string("field"));
	if( it != strings.end() ){
		return strings[std::string("field")];
	}
	else{
		std::cout << "Error: No field variable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}


void ConfigBadminton::getCancelFee(double& workC, double& weekC){
	std::map<std::string, double> doubles = getDoubles();
	std::map<std::string, double>::iterator it;
	it = doubles.find(std::string("weekendCancel"));
	if( it != doubles.end() ){
		if( it->second >= 0 && it->second <= 1.0 ){
			weekC = doubles[std::string("weekendCancel")];
		}
		else{
			std::cout << "Error: weekendCancel should be range 0 to 1!" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else{
		std::cout << "Error: No weekendCancel variable!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	// find "workdayCancel".
	it = doubles.find(std::string("workdayCancel"));
	if( it != doubles.end() ){
		if( it->second >= 0 && it->second <= 1.0 ){
			workC = doubles[std::string("workdayCancel")];
		}
		else{
			std::cout << "Error: workdayCancel should be range 0 to 1!" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else{
		std::cout << "Error: No workdayCancel variable!" << std::endl;
		exit(EXIT_FAILURE);
	}
}


void ConfigBadminton::getOrderFee(std::vector<int>& weekF, std::vector<int>& workF){
	std::map<std::string, int> ints = getInts();
	for(int i=0; i<ints.size()/4; ++i){
		for(int j=ints[std::string("timeStart") + char('1' + i)]; j<ints[std::string("timeEnd") + char('1' + i)]; ++j){
			weekF[j] = ints[std::string("weekFee") + char('1' + i)];
			workF[j] = ints[std::string("workFee") + char('1' + i)];
		}
	}
}
