#ifndef RECORD_H
#define RECORD_H
#include <string>

class record
{
	public:
		record();
		record(int y, int m, int d, int s, int e, double charge_p);
		~record();
		
		bool setDate(int y, int m, int d);
		bool setTimes(int s, int e);
		void getDate(int& y, int& m, int& d);
		void getTimes(int& start, int & end);
		bool dateIsValid(int y, int m, int d);
		bool timeIsValid(int s, int e);
		double getCharge();
		double setCharge(double total);
		bool operator<(record& b);
		bool operator==(record& b);
	protected:
		int year;
		int month;
		int day;
		int time_s;
		int time_e;
		double charge;
};

class OrderRecord : public record
{
	public:
		OrderRecord(std::string user, int y, int m, int d, int s, int e, double charge_p);
		~OrderRecord();
		bool setUserID(std::string user);
		std::string getUserID();
	private:
		std::string userID;
};

#endif
