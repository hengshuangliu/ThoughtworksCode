#ifndef BADMINTONCONTAINER_H
#define BADMINTONCONTAINER_H
#include "BadmintonField.h"
#include <vector>
#include <string>
#include <ostream>

class BadmintonContainer {
	public:
		// initialize the container of the badminton fields.
		bool initializeContainer(std::string fields, double& workC, double& weekC, std::vector<int>& weekF, std::vector<int>& workF);
		// do operation: take a order or cancel.
		bool operateBadminton(std::string user, int y, int m, int d,\
		                      int time_start, int time_end, char fieldN, char operate);
		// output total incoming information.
		bool printTotalFee(std::ostream& outStream);
		
	private:
		std::vector<BadmintonField> badmintons;  // container for Badminton fields.
};

class ResolveCommand {
	public:
		// resolve the input string of the command.
		bool resolve(std::string input, std::string& user, int& y, int& m, int& d,\
		             int& time_start, int& time_end, char& fieldN, char& operate);
		// resolve the date from the string date.
		bool resolveDate(std::string date, int& y, int& m, int& d);
		// resolve the time from the string time.
		bool resolveTime(std::string times, int& time_start, int& time_end);
		std::vector<std::string> split(std::string input, std::string seperator);
};

#endif
