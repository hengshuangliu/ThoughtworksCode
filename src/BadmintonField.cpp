#include "BadmintonField.h"
#include <vector>
#include <iostream>
#include <ostream>
#include <algorithm>

BadmintonField::BadmintonField() {
	std::vector<int> tmp(24, -1);
	for(int i=0; i<tmp.size(); ++i) {
		weekendFee.push_back(tmp[i]);
		workdayFee.push_back(tmp[i]);
	}

	workCancel = 0;
	weekCancel = 0;
}


BadmintonField::~BadmintonField() {
}


void BadmintonField::setBadmintonField(char num, std::vector<int> weekF, std::vector<int> workF, double workC, double weekC) {
	fieldNum = num;

	for(int j=0; j<weekendFee.size(); ++j) {
		weekendFee[j] = weekF[j];
		workdayFee[j] = workF[j];
	}

	workCancel = workC;
	weekCancel = weekC;
}


void BadmintonField::getBadmintonField(char& num, std::vector<int>& weekF, std::vector<int>& workF, double& workC, double& weekC) {
	num = fieldNum;

	for(int j=0; j<weekendFee.size(); ++j) {
		weekF[j] = weekendFee[j];
		workF[j] = workdayFee[j];
	}

	workC = workCancel;
	weekC = weekCancel;
}


bool BadmintonField::takeOrder(std::string user, int y, int m, int d, int s, int e) {
	std::vector<OrderRecord>::iterator it = findOrderRecord(y, m, d, s, e);
	if( it != orderRecords.end() ) {
		std::cout << "Error: the booking conflicts with existing bookings!"  << std::endl;
		return false;
	} else {
		if(weekendFee[s] == -1 || weekendFee[e-1] == -1) {
			std::cout << "Error: the booking is invalid!" << std::endl;
			return false;
		}
		orderRecords.push_back(OrderRecord(user, y, m, d, s, e, orderFee(y, m, d, s, e) ) );
		std::cout << "Success: the booking is accepted!" << std::endl;
		return true;
	}
}


bool BadmintonField::cancel(std::string user, int y, int m, int d, int s, int e) {
	std::vector<OrderRecord>::iterator it = findOrderRecord(y, m, d, s, e);
	if( it == orderRecords.end() ) {
		std::cout << "Error: the booking being cancelled does not exist!" << std::endl;
		return false;
	}

	int s_tmp=0, e_tmp=0;
	it->getTimes(s_tmp, e_tmp);
	if( user == it->getUserID() && s_tmp == s && e_tmp == e) {
		orderRecords.erase(it);

		std::vector<record>::iterator it_record = findRecord(y, m, d, s, e);
		if( it_record != records.end() ) {
			it_record ->setCharge( it_record ->getCharge() +  cancelFee(y, m, d, s, e));
		} else {
			records.push_back(record(y, m, d, s, e, cancelFee(y, m, d, s, e) ) );
		}
		std::cout << "Success: the booking is accepted!" << std::endl;
		return true;
	} else {
		std::cout << "Error: the booking being cancelled does not exist!" << std::endl;
		return false;
	}
}


double BadmintonField::getCancelFee() {
	double sum = 0;
	for(std::vector<record>::iterator it=records.begin(); it!=records.end(); ++it) {
		sum += it->getCharge();
	}
	return sum;
}


double BadmintonField::getOrderFee() {
	double sum = 0;
	for(std::vector<OrderRecord>::iterator it=orderRecords.begin(); it!=orderRecords.end(); ++it) {
		sum += it->getCharge();
	}
	return sum;
}


char BadmintonField::getFieldNum() {
	return fieldNum;
}


double BadmintonField::printRecords(std::ostream& oser) {
	oser << "场地:" << fieldNum << std::endl;
	double sum = 0;
	// sorting for print information.
	std::sort(records.begin(), records.end());
	std::sort(orderRecords.begin(), orderRecords.end());

	std::vector<record>::iterator it=records.begin();
	std::vector<OrderRecord>::iterator it_order=orderRecords.begin();
	while(it!=records.end() || it_order!=orderRecords.end()) {
		if(it == records.end() ) {
			printOrderRecord(oser, sum, it_order);
			++it_order;
		} else if(it_order == orderRecords.end()) {
			printRecord(oser, sum, it);
			++it;
		} else {
			if( (*it)<(*it_order) ) {
				printRecord(oser, sum, it);
				++it;
			} else {
				printOrderRecord(oser, sum, it_order);
				++it_order;
			}
		}
	}
	oser << "小计：" <<  sum << "元" <<std::endl;
	return sum;
}


void BadmintonField::printRecord(std::ostream& oser, double& sum, std::vector<record>::iterator& it) {
	if(it!=records.end()) {
		int y=0, m=0, d=0;
		int time_s=0, time_e=0;
		it->getDate(y, m, d);
		it->getTimes(time_s, time_e);
		double charge = it->getCharge();
		sum += charge;
		if(m<10) {
			oser << y << "-0" << m;
		} else {
			oser << y << "-" << m;
		}
		if(d<10) {
			oser << "-0";
		} else {
			oser << "-";
		}
		oser<< d << " " << time_s << ":00~" << time_e << ":00" << " 违约金 " << charge << "元" << std::endl;
	}
}


void BadmintonField::printOrderRecord(std::ostream& oser, double& sum, std::vector<OrderRecord>::iterator& it_order) {
	if(it_order!=orderRecords.end() ) {
		int y=0, m=0, d=0;
		int time_s=0, time_e=0;
		it_order->getDate(y, m, d);
		it_order->getTimes(time_s, time_e);
		double charge = it_order->getCharge();
		sum += charge;
		if(m<10) {
			oser << y << "-0" << m;
		} else {
			oser << y << "-" << m;
		}
		if(d<10) {
			oser << "-0";
		} else {
			oser << "-";
		}
		oser << d << " " << time_s << ":00~" << time_e << ":00" << " " << charge << "元" << std::endl;
	}
}


double BadmintonField::orderFee(int y, int m, int d, int s, int e) {
	if( m == 1 || m == 2 ) {
		m += 12;
		y --;
	}
	int week = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7; // calculate week: 0-6;
	double sum = 0;
	if(week > 4) {
		for( int i=s; i<e; ++i) {
			sum += weekendFee[i];
		}
	} else {
		for( int i=s; i<e; ++i) {
			sum += workdayFee[i];
		}
	}
	return sum;
}


double BadmintonField::cancelFee(int y, int m, int d, int s, int e) {
	if( m == 1 || m == 2 ) {
		m += 12;
		y --;
	}
	int week = (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7; // calculate week: 0-6;
	double sum = 0;
	if(week > 4) {
		for( int i=s; i<e; ++i) {
			sum += weekendFee[i];
		}
		sum = weekCancel * sum;
	} else {
		for( int i=s; i<e; ++i) {
			sum += workdayFee[i];
		}
		sum = workCancel * sum;
	}
	return sum;
}


std::vector<OrderRecord>::iterator BadmintonField::findOrderRecord(int y, int m, int d, int s, int e) {
	std::vector<OrderRecord>::iterator it = orderRecords.begin();
	while(it != orderRecords.end()) {
		int y_t, m_t, d_t;
		int time_s, time_e;
		it->getDate(y_t, m_t, d_t);
		it->getTimes(time_s, time_e);
		if( y_t == y && m_t == m && d_t == d && !( s >= time_e || e <=time_s) ) {
			return it;
		}
		++it;
	}
	return it;
}


std::vector<record>::iterator BadmintonField::findRecord(int y, int m, int d, int s, int e) {
	std::vector<record>::iterator it = records.begin();
	while(it != records.end()) {
		int y_t, m_t, d_t;
		int time_s, time_e;
		it->getDate(y_t, m_t, d_t);
		it->getTimes(time_s, time_e);
		if( y_t == y && m_t == m && d_t == d && s == time_s && e == time_e ) {
			return it;
		}
		++it;
	}
	return it;
}
