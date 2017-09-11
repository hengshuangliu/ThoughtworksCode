#ifndef BADMINTONFIELD_H
#define BADMINTONFIELD_H
#include <vector>
#include <ostream>
#include "record.h"

class BadmintonField
{
	public:
		BadmintonField();
		~BadmintonField();
		// set basic variables for the badmintonfield.
		void setBadmintonField(char num, std::vector<int> weekF, std::vector<int> workF, double workC, double weekC);
		void getBadmintonField(char& num, std::vector<int>& weekF, std::vector<int>& workF, double& workC, double& weekC);
		// take a order or cancel in the badminton field.
		bool takeOrder(std::string user, int y, int m, int d, int s, int e);
		bool cancel(std::string user, int y, int m, int d, int s, int e);
		// get the cancel fee or order fee.
		double getCancelFee();
		double getOrderFee();
		char getFieldNum();
		
		double orderFee(int y, int m, int d, int s, int e); // calculate orderFee;
		double cancelFee(int y, int m, int d, int s, int e); // calculate cancelFee;
		std::vector<OrderRecord>::iterator findOrderRecord(int y, int m, int d, int s, int e);
		std::vector<record>::iterator findRecord(int y, int m, int d, int s, int e);
		
		// print element in the records vector.
		double printRecords(std::ostream& oser);
		void printRecord(std::ostream& oser, double& sum, std::vector<record>::iterator& it);
		void printOrderRecord(std::ostream& oser, double& sum, std::vector<OrderRecord>::iterator& it_order);
		
	protected:
		char fieldNum;
		std::vector<int> weekendFee;
		std::vector<int> workdayFee;
		double workCancel;
		double weekCancel;
		std::vector<OrderRecord> orderRecords;  // This vector for Ordering records.
		std::vector<record> records;    // This vector for cancel records.
};

#endif
