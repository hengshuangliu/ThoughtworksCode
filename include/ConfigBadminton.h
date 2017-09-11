#ifndef CONFIGBADMINTON_H
#define CONFIGBADMINTON_H
#include "ConfigTool.h"
#include <vector>

class ConfigBadminton : public ConfigTool
{
	public:
		ConfigBadminton(std::string fileName);
		~ConfigBadminton();
		
		// This method return the "Field" variable.
		std::string getFields();
		void getCancelFee(double& workC, double& weekC);
		// std::vector need to be constructed with size of 24.
		void getOrderFee(std::vector<int>& weekF, std::vector<int>& workF);
};

#endif
