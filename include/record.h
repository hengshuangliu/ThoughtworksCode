#ifndef RECORD_H
#define RECORD_H
#include <string>

class record
{
	public:
		record();
		
		// y: year, m: month, d:day, s: started time, e: end time, charge_p: charge for this record.
		record(int y, int m, int d, int s, int e, double charge_p);
		~record();
		
		// Set date, times, charge for the record.
		bool setDate(int y, int m, int d);
		bool setTimes(int s, int e);
		double setCharge(double total);
		// get method.
		void getDate(int& y, int& m, int& d);
		void getTimes(int& start, int & end);
		double getCharge();
		// Validate the date and time interval.
		bool dateIsValid(int y, int m, int d);
		bool timeIsValid(int s, int e);
		
		// overload operator for sorting algorithm.
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

// Booking record should record the user's ID.
// This OrderRecord is inherited from record.
class OrderRecord : public record
{
	public:
		OrderRecord(std::string user, int y, int m, int d, int s, int e, double charge_p);
		~OrderRecord();
		// set and get method.
		bool setUserID(std::string user);
		std::string getUserID();
	private:
		std::string userID;
};

#endif
