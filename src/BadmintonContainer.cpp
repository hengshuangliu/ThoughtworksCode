#include "BadmintonContainer.h"
#include "BadmintonField.h"
#include <iostream>
#include <string>
#include <vector>

bool BadmintonContainer::initializeContainer(std::string fields, double& workC, double& weekC, \
        std::vector<int>& weekF, std::vector<int>& workF) {
    badmintons.clear();
    for(int i = 0; i<fields.size(); ++i){
    	BadmintonField badminton;
    	badminton.setBadmintonField(fields[i], weekF, workF, workC, weekC);
    	badmintons.push_back(badminton);
	}
	if( badmintons.empty() ){
		return false;
	}
	return true;
}


bool BadmintonContainer::operateBadminton(std::string user, int y, int m, int d,\
        int time_start, int time_end, char fieldN, char operate) {
    std::vector<BadmintonField>::iterator it;
    for( it=badmintons.begin(); it != badmintons.end(); ++it){
    	if((*it).getFieldNum() == fieldN ){
    		break;
		}
	}
	
	if( it == badmintons.end()){
		std::cout << "Error: the booking is invalid!" << std::endl;
		return false;
	}
	
    if( 'C' == operate){
    	return it->cancel(user, y, m, d, time_start, time_end);
	}else if( 'B' == operate){
		return it->takeOrder(user, y, m, d, time_start, time_end);
	}else{
		std::cout << "Error: invalid operation!" << std::endl;
		return false;
	}
}


bool BadmintonContainer::printTotalFee(std::ostream& outStream) {
	if(badmintons.size() == 0){
		return false;
	}
	outStream << "收入汇总" << std::endl;
	outStream << "---" << std::endl; 
	double sum = 0;
	for(std::vector<BadmintonField>::iterator it=badmintons.begin(); it != badmintons.end(); ++it){
		sum += it->printRecords(outStream);
		outStream << std::endl;
	}
	outStream << "---" << std::endl;
	outStream << "总计：" << sum << "元" << std::endl;
	return true;
}


bool ResolveCommand::resolve(std::string input, std::string& user, int& y, int& m, int& d,\
                             int& time_start, int& time_end, char& fieldN, char& operate) {
	std::vector<std::string> result = split(input, std::string(" "));
//	for(int i=0; i<result.size(); ++i){
//		std::cout << result[i] << std::endl;
//	}
	if(result.size() == 4) {
		operate = 'B';
	} else if(result.size() == 5) {
		if(result[4] == std::string("C")) {
			operate = 'C';
		} else {
			std::cout << "Error: the booking is invalid!" << std::endl;
			return false;
		}
	} else {
		std::cout << "Error: the booking is invalid!" << std::endl;
		return false;
	}
	
	user = result[0];
	if(result[3].size() == 1) {
		fieldN = result[3][0];
	} else {
		std::cout << "Error: the booking is invalid!" << std::endl;
		return false;
	}
	if( resolveDate(result[1], y, m, d) && resolveTime(result[2], time_start, time_end )) {
		return true;
	} else {
		std::cout << "Error: the booking is invalid!" << std::endl;
		return false;
	}
}


bool ResolveCommand::resolveDate(std::string date, int& y, int& m, int& d) {
	std::vector<std::string> result = split(date, std::string("-"));
	if(result.size() == 3) {
		if(result[0].size() == 4) {
			int y_tmp = 0;
			for(int i = 0; i<4; ++i) {
				if(result[0][i] >= '0' && result[0][i] <= '9') {
					y_tmp = 10*y_tmp + result[0][i] - '0';
				} else {
					//std::cout << "Error: the booking is invalid!" << std::endl;
					return false;
				}
			}
			y = y_tmp;
		}

		if(result[1].size() == 2) {
			int m_tmp = 0;
			for(int i = 0; i<2; ++i) {
				if(result[1][i] >= '0' && result[1][i] <= '9') {
					m_tmp = 10*m_tmp + result[1][i] - '0';
				} else {
					//std::cout << "Error: the booking is invalid!" << std::endl;
					return false;
				}
			}
			if( m_tmp > 12) {
				//std::cout << "Error: the booking is invalid!" << std::endl;
				return false;
			}
			m = m_tmp;
		}

		if(result[2].size() == 2) {
			int d_tmp = 0;
			for(int i = 0; i<2; ++i) {
				if(result[2][i] >= '0' && result[2][i] <= '9') {
					d_tmp = 10*d_tmp + result[2][i] - '0';
				} else {
					//std::cout << "Error: the booking is invalid!" << std::endl;
					return false;
				}
			}
			if( d_tmp > 12 && d_tmp == 0) {
				//std::cout << "Error: the booking is invalid!" << std::endl;
				return false;
			}
			d = d_tmp;
		}
		return true;
	} else {
		//std::cout << "Error: the booking is invalid!" << std::endl;
		return false;
	}
}


bool ResolveCommand::resolveTime(std::string times, int& time_start, int& time_end) {
	if(times.size() == 11 && times[5] == '~' && times[2] == ':' && times[8] == ':'\
	        && times[3] == '0' && times[4] == '0' && times[9] == '0' && times[10] == '0') {
		// resolve time of start.
		if(times[0] >= '0' && times[0] >= '0' && times[6] >= '0' && times[7] >= '0'\
		        && times[0] <= '9' && times[0] <= '9' && times[6] <= '9' && times[7] <= '9') {
			int s_tmp = 10*(times[0] - '0') + (times[1] - '0');
			int e_tmp = 10*(times[6] - '0') + (times[7] - '0');
			if(s_tmp > 23 || e_tmp > 23 || e_tmp <= s_tmp) {
				//std::cout << "Error: the booking is invalid!" << std::endl;
				return false;
			}
			time_start = s_tmp;
			time_end = e_tmp;
			return true;
		}
		//std::cout << "Error: the booking is invalid!" << std::endl;
		return false;

	} else {
		//std::cout << "Error: the booking is invalid!" << std::endl;
		return false;
	}
}


std::vector<std::string> ResolveCommand::split(std::string input, std::string seperator) {
	std::vector<std::string> result;
	std::string::size_type pos1, pos2;
	pos2 = input.find(seperator);
	pos1 = 0;
	while(std::string::npos != pos2) {
		result.push_back(input.substr(pos1, pos2-pos1));
		pos1 = pos2 + seperator.size();
		pos2 = input.find(seperator, pos1);
	}
	if(pos1 != input.length()) {
		result.push_back(input.substr(pos1));
	}
	return result;
}
