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

	// ------------------------------------------------------------------------------
		
		typedef std::tuple <std::string, std::map<int,int >, std::map<int,int >, int > m_config;		// container for current config
		std::vector<m_config> m_vector_configs;		// container for all configs

		int m_tmp_parm_val; // tmp variable
		int m_tmp_parm_key; // tmp variable
		std::string m_tmp_parm_object; // tmp variable

		std::map<int,int > m_a_parameters;		// config - container for a - parameters
		std::map<int,int > m_b_parameters;		// config - container for b - parameters
		int	m_stationary;		// config - stationary or not
		std::string m_object_name;		// config - object name

		bool m_config_loaded;		// config flag

	// ------------------------------------------------------------------------------

	private:
		Config(void) {};		// disable constructor
		Config (const Config &);		// disable default copy
		Config & operator = (const Config &);		// disable default copy
		void clear(void);		// clear variables

	// ------------------------------------------------------------------------------

	public:
		~Config(void) {}		// destructor

		bool check_if_config_loaded(void) { return this->m_config_loaded; };		// check if config was loaded
		void set_config(void);		// set config flag to true
		void parse_file(std::string line);		// parse line
		void clear_vector_config(void);			// clear all settings

		/**
		 * Get the size of all configs
		 *
		 * @return		int
		 */
		int get_size_of_configs(void) { return m_vector_configs.size(); };

		std::string get_size_of_configs(int i);		// get string size of all configs which were loaded
		void get_parameters(std::map<int, int> & parm, int object, int parameter);		// get parameters for current object;
		bool check_object_stationarity(int object);
		std::string get_object_name(int object);

		/*
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
		*/
		// Instance of object
		static Config & getInstance()
		{
			static Config instance; 
			return instance; 	
		};		

};

#endif