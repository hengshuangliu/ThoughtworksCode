#ifndef CONFIGTOOL_H
#define CONFIGTOOL_H

#include <string>
#include <map>

enum ConfigType {type_integer, type_string, type_double};

class ConfigTool {
	public:
		ConfigTool();
		ConfigTool(std::string fileName);
		~ConfigTool();

		void setConfigFile(std::string fileName);
		std::string getConfigFile();
		bool runConfig();
		bool runConfig(std::string fileName);
		bool intsEmpty();
		bool doublesEmpty();
		bool stringsEmpty();
		void clear();
		std::map<std::string, int> getInts();
		std::map<std::string, double> getDoubles();
		std::map<std::string, std::string> getStrings();

	private:
		std::string configFile;
		std::map<std::string, int> ints;
		std::map<std::string, double> doubles;
		std::map<std::string, std::string> strings;

		bool FilterIfAnnotations(std::string& str);
		bool VarifyVariable(const std::string& str);
		bool StringToInt(const std::string& str, int& integer);
		bool StringToDouble(const std::string& str, double& double_out);
};

#endif
