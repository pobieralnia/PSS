#ifndef __CONFIGBASE_H__
#define __CONFIGBASE_H__

#include <string>
#include <tuple>
#include <map>

class ConfigBase {

	public:
		virtual void parse_line(std::string line) = 0;
		virtual int get_size(void) = 0;
		virtual void clear_all(void) = 0;
		virtual std::string get_size(int i) = 0;
		virtual ~ConfigBase() {};
};

#endif