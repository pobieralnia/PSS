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
#include <tuple>
#include <map>
#include <sstream>
#include <vector>

public class Config : private ConfigParser
{
	// TODO:
	// 1. size of map a and b
	// 2. name of object
	// two and more objects
	

	// ------------------------------------------------------------------------------
		
		typedef std::tuple <std::string, std::map<int,int >, std::map<int,int > > m_config;
		std::vector<m_config> m_vector_configs;

		int m_a_parameters_counter;		// counter for all a parameters
		int m_b_parameters_counter;		// counter for all b parameters
		int m_object_parameters_counter;

		int m_tmp_parm_val;
		int m_tmp_parm_key;
		std::string m_tmp_parm_object;

		std::map<int,int > m_a_parameters;		// config - container for a - parameters
		std::map<int,int > m_b_parameters;		// config - container for b - parameters
		int	m_stationary;		// config - stationary or not
		std::string m_object_name;

		bool m_config_loaded;		// new config info

	// ------------------------------------------------------------------------------

	private:
		Config(void) {};		// disable constructor
		Config (const Config &);		// disable default copy
		Config & operator = (const Config &);		// disable default copy

	// ------------------------------------------------------------------------------

	public:
		~Config(void) {}		// destructor
		
		bool check_if_config_loaded(void) { return this->m_config_loaded; };		// check if new config -> never useed
		void set_config(void);
		void parse_file(std::string line);		// parse line
		void clear(void);		// initialization
		void clear_vector_config(void);

		int check_value_of_a_parm(void)	{ return this->m_a_parameters_counter; };
		std::string check_value_of_a_parm(int);		// check how many a there is string
		int check_value_of_b_parm(void)	{ return this->m_b_parameters_counter; };
		std::string check_value_of_b_parm(int);		// check how many b there is string
		std::string get_object_name_counter(int);		// check if stationary

		std::string print_ids()
		{
			std::string b;
			for(std::vector<m_config>::const_iterator i = m_vector_configs.begin(); i != m_vector_configs.end(); ++i)
			{
				 b += print_idss(*i);
			}
			return b;
		}

		std::string print_idss(const m_config & i)
		{
		   std::string c;
		   std::map<int,int> d;
		   d = std::get<1>(i);
		   for(std::map<int,int>::iterator ii=d.begin(); ii!=d.end(); ++ii)
		   {
			  std::stringstream ss;//create a stringstream
			  ss << (*ii).first;
			  c += ss.str();//return a string with the contents of the stream
			

		   }
		   return c;
		}

		// Instance of object
		static Config & getInstance()
		{
			static Config instance; 
			return instance; 	
		};		

};

#endif