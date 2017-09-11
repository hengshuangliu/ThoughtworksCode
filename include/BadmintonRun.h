#ifndef BADMINTONRUN_H
#define BADMINTONRUN_H

#include <string>
#include <ostream>

class BadmintonRun
{
	public:
		// this method is used to drive the all the modules.
		bool run(std::string configFile, std::ostream& outer);
};

#endif
