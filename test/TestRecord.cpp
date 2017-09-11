#include <iostream>
#include <vector>
#include <string>
#include "UnitTest.h"
#include "record.h"

UTEST(RecordTest)
{
	// Test Record.
	int y=0, m=0, d=0, t_s=0, t_e=0;
	record recordTest(2016, 8,29, 9, 10, 12.0);
	double charge=recordTest.getCharge();
	recordTest.getDate(y, m, d);
	EXPECT_EQ(2016, y);
	EXPECT_EQ(8, m);
	EXPECT_EQ(29, d);
	recordTest.getTimes(t_s, t_e);
	EXPECT_EQ(9, t_s);
	EXPECT_EQ(10, t_e);
	
	EXPECT_EQ(12.0, charge);
	recordTest.setCharge(13.0);
	EXPECT_EQ(13.0, recordTest.getCharge());
	
	EXPECT_EQ(true, recordTest.dateIsValid(2016, 3, 31));
	EXPECT_EQ(false, recordTest.dateIsValid(2016, 2, 31));
	EXPECT_EQ(false, recordTest.dateIsValid(2016, 4, 31));
	
	EXPECT_EQ(true, recordTest.timeIsValid(10, 13) );
	EXPECT_EQ(false, recordTest.timeIsValid(10, 10) );
	
	// Test OrderRecord.
	std::string user("U123");
	OrderRecord OrderRecordTest(user,2016, 8,29, 9, 10, 12.0);
	OrderRecordTest.getDate(y, m, d);
	EXPECT_EQ(2016, y);
	EXPECT_EQ(8, m);
	EXPECT_EQ(29, d);
	OrderRecordTest.getTimes(t_s, t_e);
	EXPECT_EQ(9, t_s);
	EXPECT_EQ(10, t_e);
	
	EXPECT_EQ(12.0, charge);
	OrderRecordTest.setCharge(13.0);
	EXPECT_EQ(13.0, OrderRecordTest.getCharge());
	
	EXPECT_EQ(true, OrderRecordTest.dateIsValid(2016, 3, 31));
	EXPECT_EQ(false, OrderRecordTest.dateIsValid(2016, 2, 31));
	EXPECT_EQ(false, OrderRecordTest.dateIsValid(2016, 4, 31));
	
	EXPECT_EQ(true, OrderRecordTest.timeIsValid(10, 13) );
	EXPECT_EQ(false, OrderRecordTest.timeIsValid(10, 10) );
	
	EXPECT_EQ(user, OrderRecordTest.getUserID());
}
