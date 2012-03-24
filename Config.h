// ---------------------------------------------------------------------------------
// Filename:	Config.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config,ConfigParser
// Usage:		
//
// Config::getInstance().init();
// Config::getInstance().set_new_config();
// Config::getInstance().parse_file( <string> );	
//
// Class for creating config object and storing main variables, after first use it creates a copy of it (nie zrobione)
// ---------------------------------------------------------------------------------

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ConfigParser.h"
#include <string>
#include <map>

public class Config : private ConfigParser
{
	private:

		// ------------------------------------------------------------------------------

		int m_a_parameters_counter;		// counter for all a parameters
		int m_b_parameters_counter;		// counter for all b parameters

		int m_tmp_parm_val;
		int m_tmp_parm_key;

		std::map<int,int > m_a_parameters;		// config - container for a - parameters
		std::map<int,int > m_b_parameters;		// config - container for b - parameters
		int	m_stationary;		// config - stationary or not

		bool m_new_config;		// new config info
		// ------------------------------------------------------------------------------

		Config(void) {};		// disable constructor
		Config (const Config &);		// disable default copy
		Config & operator = (const Config &);		// disable default copy

		// ------------------------------------------------------------------------------

	public:
		~Config(void) {}		// destructor
		
		bool check_if_new_config(void) { return this->m_new_config; };		// check if new config -> never useed
		void parse_file(std::string line);		// parse line
		void init(void);		// initialization
		void disable_new_config(void);
		void set_new_config(void);
			
		int check_value_of_a_parm(void)	{ return this->m_a_parameters_counter; };
		std::string check_value_of_a_parm(int);		// check how many a there is string
		int check_value_of_b_parm(void)	{ return this->m_b_parameters_counter; };
		std::string check_value_of_b_parm(int);		// check how many b there is string
		int check_if_stationary_parm(void)	{ return this->m_stationary; };
		std::string check_if_stationary_parm(int);		// check if stationary

		// Instance of object
		static Config & getInstance()
		{
			static Config instance; 
			return instance; 	
		};		

};

#endif