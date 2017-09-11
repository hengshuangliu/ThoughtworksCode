#include <iostream>
#include <vector>
#include <string>
#include "UnitTest.h"
#include "BadmintonField.h"


UTEST(BadmintonFieldTest) {
	BadmintonField badmintonFieldTest;
	char num='A';
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
	badmintonFieldTest.setBadmintonField(num, weekF, workF, workC, weekC);
	EXPECT_EQ(true, badmintonFieldTest.takeOrder(std::string("U001"), 2017, 9, 11, 18, 19) );
	EXPECT_EQ(false, badmintonFieldTest.cancel(std::string("U001"), 2017, 9, 11, 18, 20) );
	
	EXPECT_EQ(true, badmintonFieldTest.takeOrder(std::string("U002"), 2017, 9, 10, 9, 10) );
	EXPECT_EQ(true, badmintonFieldTest.takeOrder(std::string("U003"), 2017, 9, 10, 12, 14) );
	EXPECT_EQ(true, badmintonFieldTest.cancel(std::string("U002"), 2017, 9, 10, 9, 10) );
	
	EXPECT_EQ(175, badmintonFieldTest.printRecords(std::cout) );
}
