// ---------------------------------------------------------------------------------
// Filename:	ConfigParser.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ConfigParser
// ---------------------------------------------------------------------------------

#ifndef __CONFIGPARSER_H__
#define __CONFIGPARSER_H__

#include <string>

/**
 * @class ConfigParser ConfigParser.h
 * @brief Class for parsing from string line
 *
 * It has six hree methods regex_b_parameter, regex_a_parameter, regex_stationary, regex_k, regex_object_name, regex_end_of_config. 
 * Each method return bool - True if success, False for failure. For parsing is used regex library.
 */
private class ConfigParser
{
	protected:
		bool regex_b_parameter(std::string line, int * b_val, int * b_key);
		bool regex_a_parameter(std::string line, int * a_val, int * a_key);
		bool regex_stationary(std::string line);
		bool regex_object_name(std::string line, std::string & object_name);
		bool regex_end_of_config(std::string line);
		bool regex_k(std::string line, int * k);

	public:
		ConfigParser(void) {};
		virtual ~ConfigParser(void) {};

};

#endif

