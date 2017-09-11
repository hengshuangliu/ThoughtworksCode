#ifndef BADMINTONCONTAINER_H
#define BADMINTONCONTAINER_H
#include "BadmintonField.h"
#include <vector>
#include <string>
#include <ostream>

class BadmintonContainer {
	public:
		bool initializeContainer(std::string fields, double& workC, double& weekC, std::vector<int>& weekF, std::vector<int>& workF);
		bool operateBadminton(std::string user, int y, int m, int d,\
		                      int time_start, int time_end, char fieldN, char operate);
		bool printTotalFee(std::ostream& outStream);
		
	private:
		std::vector<BadmintonField> badmintons;
};

class ResolveCommand {
	public:
		bool resolve(std::string input, std::string& user, int& y, int& m, int& d,\
		             int& time_start, int& time_end, char& fieldN, char& operate);
		bool resolveDate(std::string date, int& y, int& m, int& d);
		bool resolveTime(std::string times, int& time_start, int& time_end);
		std::vector<std::string> split(std::string input, std::string seperator);
};

#endif
