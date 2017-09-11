#ifndef CONFIGBADMINTON_H
#define CONFIGBADMINTON_H
#include "ConfigTool.h"
#include <vector>

class ConfigBadminton : public ConfigTool
{
	public:
		ConfigBadminton(std::string fileName);
		~ConfigBadminton();
		
		std::string getFields();
		void getCancelFee(double& workC, double& weekC);
		void getOrderFee(std::vector<int>& weekF, std::vector<int>& workF);
};

#endif
