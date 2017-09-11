#include "ConfigTool.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>

ConfigTool::ConfigTool(std::string fileName) {
	ConfigTool();
	setConfigFile(fileName);
}

ConfigTool::ConfigTool() {
	configFile = std::string();
	ints = std::map<std::string, int>();
	doubles = std::map<std::string, double>();
	strings = std::map<std::string, std::string>();
}

ConfigTool::~ConfigTool() {}

void ConfigTool::setConfigFile(std::string fileName) {
	configFile = fileName;
}

std::string ConfigTool::getConfigFile() {
	return configFile;
}

bool ConfigTool::runConfig() {
	if(configFile.empty()) {
		std::cout << "error: no fileName for configure file." << std::endl;
		return false;
	}

	clear();
	std::ifstream fin;
	fin.open(configFile.c_str());
	if(fin.is_open() == false) {
		std::cerr << "Can't open file.\n";
		return false;
	}
	std::string item;
	int line=0;
	ConfigType config_t = type_integer;
	while(fin) {
		getline(fin, item);
		if(!fin) {
			break;
		}
		++line;
		if(FilterIfAnnotations(item)) { // delete annotations.
			continue;
		}
		// cout << item << endl;
		if(item[0] == '<') {            // judge <type>.
			if(item == "<string>") {
				config_t = type_string;
			} else if(item == "<double>") {
				config_t = type_double;
			} else if(item == "<integer>") {
				config_t = type_integer;
			} else {
				std::cout << "line " << line << ":syntax error!" << std::endl;
				return false;
			}
		} else {           // extract variable.
			int left = 0, right = 0;
			while((right = item.find(';',left)) != std::string::npos) {
				std::string sub = item.substr(left, right-left);
				// cout << sub << endl;
				left = right+1;
				if(!VarifyVariable(sub)) {
					std::cout << "line " << line << ":variable invalid!" << std::endl;
					return false;
				} else {
					std::string sub_key;
					std::string sub_var;
					int var_s = 0;
					if((var_s=sub.find('=',0)) != std::string::npos) {
						if(var_s==sub.size()-1) {
							std::cout << "line " << line << ":No Variable!" << std::endl;
							return false;
						}
						sub_var = sub.substr(var_s+1, sub.size()-var_s-1);
						sub_key = sub.substr(0, var_s);
					} else {
						std::cout << "line " << line << ":variable invalid!" << std::endl;
						return false;
					}
					switch(config_t) {
						case type_integer: {
							int integer;
							if(StringToInt(sub_var,integer)) {
								// cout << sub_key <<":" << c << endl;
								std::map<std::string, int>::iterator it_int;
								if(ints.find(sub_key) == ints.end() ) {
									ints.insert(std::pair<std::string, int>(sub_key, integer) );
								} else {
									std::cout << "line " << line << ":Repeat define variable " << std::endl;
									return false;
								}
							} else {
								std::cout << "line " << line << ":variable invalid!(Not Integer)" << std::endl;
								return false;
							}
							break;
						}
						case type_double: {
							double double_out;
							if(StringToDouble(sub_var, double_out)) {
								// cout << sub_key <<":" << double_out << endl;
								if(doubles.find(sub_key) == doubles.end() ) {
									doubles.insert(std::pair<std::string, double>(sub_key,double_out));
								} else {
									std::cout << "line " << line << ":Repeat define variable " << std::endl;
									return false;
								}
							} else {
								std::cout << "line " << line << ":variable invalid!(Not Double)" << std::endl;
								return false;
							}
							break;
						}
						case type_string: {
							// cout << sub_key <<":" << sub_var << endl;
							if(strings.find(sub_key) == strings.end() ) {
								strings.insert(std::pair<std::string, std::string>(sub_key,sub_var));
							} else {
								std::cout << "line " << line << ":Repeat define variable " << std::endl;
								return false;
							}
							break;
						}
						default: {
							break;
						}
					}

				}
			}
		}
	}
	std::cout << "Done\n";
	fin.close();
	return true;
}
bool ConfigTool::runConfig(std::string fileName) {
	if(fileName.empty() && configFile.empty()) {
		std::cout << "error: no fileName for configure file." << std::endl;
		return false;
	} else if(!fileName.empty()) {
		setConfigFile(fileName);
	}
	return runConfig();
}


bool ConfigTool::intsEmpty() {
	return ints.empty();
}
bool ConfigTool::doublesEmpty() {
	return doubles.empty();
}
bool ConfigTool::stringsEmpty() {
	return strings.empty();

}
void ConfigTool::clear() {
	ints.clear();
	doubles.clear();
	strings.clear();
}

std::map<std::string, int> ConfigTool::getInts() {
	return ints;
}
std::map<std::string, double> ConfigTool::getDoubles() {
	return doubles;
}
std::map<std::string, std::string> ConfigTool::getStrings() {
	return strings;
}

bool ConfigTool::FilterIfAnnotations(std::string& str) {
	int index = 0;
	if(!str.empty()) {
		while((index = str.find(' ',index)) != std::string::npos) {
			str.erase(index, 1);
		}
		index = 0;
		if((index = str.find("//", 0)) != std::string::npos) {
			str.erase(index, str.size()-index);
		}
		return 	str.empty();
	} else {
		return true;
	}
}

bool ConfigTool::VarifyVariable(const std::string& str) {
	int index = 0;
	if(str[0] == '_' || (str[0]>'a'&&str[0]<'z') || (str[0]>'A'&&str[0]<'Z')) {
		if((index = str.find('=',0)) != std::string::npos) {
			for(int i=1; i<index; ++i) {
				if(str[i] == '_' || isalnum(str[i])) {
					continue;
				} else {
					return false;
				}
			}
		} else {
			return false;
		}

	} else {
		return false;
	}
	return true;
}

bool ConfigTool::StringToInt(const std::string& str, int& integer) {
	for(int i=0; i<str.size(); ++i) {
		if(!isdigit(str[i])) {
			integer = 0;
			return false;
		}
	}
	integer = atoi(str.c_str());
	return true;
}

bool ConfigTool::StringToDouble(const std::string& str, double& double_out) {
	int dot=0;
	if(!isdigit(str[0])) {
		double_out = 0;
		return false;
	}
	for(int i=1; i<str.size(); ++i) {
		if(str[i] == '.') {
			dot ++;
			continue;
		}
		if( (!isdigit(str[i])) || dot > 1) {
			double_out = 0;
			return false;
		}
	}
	double_out = atof(str.c_str());
	return true;
}


