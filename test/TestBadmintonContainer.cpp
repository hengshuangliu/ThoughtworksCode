#include <iostream>
#include <vector>
#include <string>
#include "UnitTest.h"
#include "BadmintonContainer.h"

UTEST(BadmintonContainerTest) {
	// Test the method of resolveCommand.
	ResolveCommand resolver;
	std::string user;
	int y, m , d, time_start, time_end;
	char fieldN, operate;

	// Test invalid command.
	EXPECT_EQ(false, resolver.resolve( std::string("abcdefghijklmnopqrst1234567890"), user, y, m, d,\
	                                   time_start, time_end, fieldN, operate ) );
	// Test valid command.
	EXPECT_EQ(true, resolver.resolve( std::string("U001 2016-06-02 20:00~22:00 A C"), user, y, m, d,\
	                                   time_start, time_end, fieldN, operate ) );
	EXPECT_EQ(std::string("U001"), user);
	EXPECT_EQ(2016, y);
	EXPECT_EQ(6, m);
	EXPECT_EQ(2, d);
	EXPECT_EQ(20, time_start);
	EXPECT_EQ(22, time_end);
	EXPECT_EQ('A', fieldN);
	EXPECT_EQ('C', operate);
	
	
	// Test BadmintonContainer;
	int week_tmp[24] = {-1, -1, -1, -1, -1, -1, -1, -1,\
	                   30, 30, 30, 30, 50, 50, 50, 50,\
					   50, 50, 80, 80, 60, 60, -1, -1};
	int work_tmp[24] = {-1, -1, -1, -1, -1, -1, -1, -1,\
	                   40, 40, 40, 40, 50, 50, 50, 50,\
					   50, 50, 60, 60, 60, 60, -1, -1};
	double workC = 0.25;
	double weekC = 0.5;
	std::vector<int> weekF(week_tmp, week_tmp + 24);
	std::vector<int> workF(work_tmp, work_tmp + 24);
	BadmintonContainer badmintons;
	EXPECT_EQ(true, badmintons.initializeContainer(std::string("ABCD"), workC, weekC, weekF, workF) );
	// take a valid order for test.
	EXPECT_EQ(true, badmintons.operateBadminton(std::string("U001"), 2017, 9, 11, 18, 19, 'A', 'B' ) );
	// take a invalid cancel.
	EXPECT_EQ(false, badmintons.operateBadminton(std::string("U001"), 2017, 9, 11, 18, 20, 'A', 'C') );
	// take a valid order for test.
	EXPECT_EQ(true, badmintons.operateBadminton(std::string("U002"), 2017, 9, 10, 9, 10, 'A', 'B') );
	// take a valid order for test.
	EXPECT_EQ(true, badmintons.operateBadminton(std::string("U003"), 2017, 9, 10, 12, 14, 'A', 'B') );
	// take a valid cancel for test.
	EXPECT_EQ(true, badmintons.operateBadminton(std::string("U002"), 2017, 9, 10, 9, 10, 'A', 'C') );
	// print total fee.
	badmintons.printTotalFee(std::cout);
}
