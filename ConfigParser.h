// ---------------------------------------------------------------------------------
// Filename:	ConfigParser.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ConfigParser
// 
// Class for parsing string lines, it has three methods regex_b_parameter, regex_a_parameter,
// regex_stationary. Each method return bool - True if success, False for failure.
// For parsing is used regex library.
// ---------------------------------------------------------------------------------

#ifndef __CONFIGPARSER_H__
#define __CONFIGPARSER_H__

#include <string>

private class ConfigParser
{
	protected:
		bool regex_b_parameter(std::string line, int * b_val, int * b_key);
		bool regex_a_parameter(std::string line, int * a_val, int * a_key);
		bool regex_stationary(std::string line);

	public:
		ConfigParser(void) {};
		virtual ~ConfigParser(void) {};

};

#endif

