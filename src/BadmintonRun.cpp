#include <iostream>
#include "BadmintonRun.h"
#include "ConfigBadminton.h"
#include "BadmintonContainer.h"


bool BadmintonRun::run(std::string configFile, std::ostream& outer){
	ConfigBadminton cfgBadminton(configFile);
	if( !cfgBadminton.runConfig() ){
		std::cout << "Error: Configure failed!" << std::endl;
		return false;
	}
	std::string fields = cfgBadminton.getFields();
	double workC, weekC;
	cfgBadminton.getCancelFee(workC, weekC);
	std::vector<int> weekF(24, -1);
	std::vector<int> workF(24, -1);
	cfgBadminton.getOrderFee(weekF, workF);
	
//	std::cout << "---initializing---" << std::endl;
	BadmintonContainer badmintonCon;
	if(!badmintonCon.initializeContainer(fields, workC, weekC, weekF, workF) ){
		std::cout << "Error: initialize failed!" << std::endl;
		return false;
	}
//	std::cout << "---initialize Success!" << std::endl;
	
	ResolveCommand resolver;
	std::string command;
	std::string user;
	int y, m, d, time_start, time_end;
	char fieldN, operate;
	while(getline(std::cin, command)){
		if( command.empty() ){
			break;
		}
		if(resolver.resolve(command, user, y, m, d, time_start, time_end, fieldN, operate)){
			badmintonCon.operateBadminton(user, y, m, d, time_start, time_end, fieldN, operate);
		}
	}
	
	// print total fee;
	return badmintonCon.printTotalFee(outer);
	
}
