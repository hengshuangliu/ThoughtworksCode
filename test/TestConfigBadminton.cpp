#include "UnitTest.h"
#include "ConfigBadminton.h"
#include <iostream>
#include <vector>
#include <string>

UTEST(ConfigBadmintonTest)
{
	ConfigBadminton configBadmintonTest(".\\test.config");
	double workC, weekC;
	std::vector<int> weekF(24, -1);
	std::vector<int> workF(24, -1);
	configBadmintonTest.runConfig();
	configBadmintonTest.getCancelFee(workC, weekC);
	configBadmintonTest.getOrderFee(weekF, workF);
	
	std::cout << "输出配置文件信息：" << std::endl;
	std::cout << "Fields: " << configBadmintonTest.getFields() << std::endl;
	std::cout << "workC:" << workC << " weekC:" << weekC << std::endl;
	for(int i=0; i<24; ++i){
		std::cout << "time:" << i << " weekF:" << weekF[i] << " workF:" << workF[i] << std::endl;
	}
}
