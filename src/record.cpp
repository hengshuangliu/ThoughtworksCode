#include "record.h"
#include <string>
#include <iostream>

record::record() {
	setDate(0, 0, 0);
	setTimes(0, 0);
	charge = 0;
}


record::record(int y, int m, int d, int s, int e, double charge_p){
	setDate(y, m, d);
	setTimes(s, e);
	charge = charge_p;
}

record::~record() { }

bool record::setDate(int y, int m, int d) {
	if(dateIsValid(y, m, d)){
		year = y;
		month = m;
		day = d;
		return true;
	}
	else{
		return false;
	}
}


bool record::setTimes(int s, int e){
	if( timeIsValid(s, e) ){
		time_s = s;
		time_e = e;
		return true;
	}
	else{
		return false;
	}
}


void record::getDate(int& y, int& m, int& d){
	y = year;
	m = month;
	d = day;
}


void record::getTimes(int& start, int & end){
	start = time_s;
	end = time_e;
}


bool record::dateIsValid(int y, int m, int d){
	if(y < 0 || m <= 0 || m > 12 || d <= 0 || d > 31) {
		std::cout << "date is invalid." << std::endl;
		return false;
	}
	
	if(1 == m || 3 == m || 5 == m || 7 == m || 8 == m || 10 == m || 12 == m){
        return true;
    }
    else{
    	if( 31 == d){
    		return false;
		}
	}

	// when the year is leap.
	if(((y%4 == 0) && (y%100 != 0)) || (y%400 == 0)) { // is leap year.
		if(2 == m && (30 == d || 31 == d)) {
			std::cout << "date is invalid." << std::endl;
			return false;
		}
	}
	else{
		if(2 == m && (29 == d || 30 == d || 31 == d)) {
			std::cout << "date is invalid." << std::endl;
			return false;
		}
	}
	return true;
}


bool record::timeIsValid(int s, int e){
	if( s >= e || s < 0 || e < 0 || s > 23 || e > 23 ){
		std::cerr << "time is invalid" << std::endl;
		return false;
	}
	return true;
}


double record::getCharge(){
	return charge;
}


double record::setCharge(double total){
	charge = total;
	return total;
}


bool record::operator<(record& b){
	int y, m, d;
	int s, e;
	b.getDate(y, m, d);
	b.getTimes(s, e);
	if( year < y){
		return true;
	}
	if( year == y && month < m){
		return true;
	}
	if( year == y && month == m && day < d){
		return true;
	}
	if( year == y && month == m && day == d && time_s < s){
		return true;
	}
	if(year == y && month == m && day == d && time_s == s &&  time_e < e){
		return true;
	}
	return false;
}


bool record::operator==(record& b){
	int y, m, d;
	int s, e;
	b.getDate(y, m, d);
	b.getTimes(s, e);
	return year == y && month == m && day == d && time_s == s &&  time_e == e;
}


OrderRecord::OrderRecord(std::string user, int y, int m, int d, int s, int e, double charge_p): record(y, m, d, s, e, charge_p){
	setUserID(user);
}


OrderRecord::~OrderRecord(){}


bool OrderRecord::setUserID(std::string user){
	userID = user;
}


std::string OrderRecord::getUserID(){
	return userID;
}
