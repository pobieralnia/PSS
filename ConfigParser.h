// ---------------------------------------------------------------------------------
// Filename:	ConfigParser.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ConfigParser
// ---------------------------------------------------------------------------------

#ifndef __CONFIGPARSER_H__
#define __CONFIGPARSER_H__

#include <string>
#include <map>

/**
 * @class ConfigParser ConfigParser.h
 * @brief Class for parsing from string line
 *
 * Each method for object return bool - True if success, False for failure. For parsing is used regex library.
 * Method for generator config return void, we pass by reference map to fill it
 */
class ConfigParser
{
	protected:
		bool regex_b_parameter(std::string line, double * b_val, int * b_key);
		bool regex_a_parameter(std::string line, double * a_val, int * a_key);
		bool regex_stationary(std::string line);
		bool regex_end_of_config(std::string line);
		bool regex_k(std::string line, double * k);
		bool regex_da(std::string line, int * da);
		bool regex_db(std::string line, int * db);
		bool regex_noise(std::string line, double * noise);
		void regex_generator_parameter(std::string line, std::map<std::string, double > & parm);
		void regex_regulator_parameter(std::string line, std::map<std::string, double > & parm);

	public:
		ConfigParser(void) {};
		virtual ~ConfigParser(void) {};

};

#endif