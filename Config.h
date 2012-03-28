// ---------------------------------------------------------------------------------
// Filename:	Config.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config,ConfigParser	
// TODO:		dB,dA - regex methods, default values ? , converter map -> deque,vector (fill with 0 empty keys, template member function get_parameters ???????)
//				v.reserve(tmap.size());
//				copy(tmap.begin(), tmap.begin() + tmap.size(), v.begin());
//
//	Progress	85% finish
// ---------------------------------------------------------------------------------

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ConfigParser.h"
#include <string>
#include <tuple>
#include <map>
#include <vector>

/**
 * @class		Config Config.h
 * @brief		Main class for keeping settings inside containers and variables
 *
 * It inherit from ConfigParser class where are stored methods for parsing values from string line. The main variables are k, polyniomal A,B, stationarity, object name.
 *
 * Simply usage:
 * Config::getInstance().clear_vector_config();
 * Config::getInstance().parse_file( <string> );		
 * Config::getInstance().set_config();
 *
 * Exceptions:
 * @see		set_config();
 * @see		get_parameters();
 * @see		check_object_stationarity();
 * @see		get_object_name();
 */
public class Config : private ConfigParser
{

	// ------------------------------------------------------------------------------
		
	typedef std::tuple <std::string, std::map<int,int >, std::map<int,int >, int, int > m_config;	// container for current config
	std::vector<m_config> m_vector_configs;	// container for all configs

	static const int POLYNOMIAL_A = 0;
	static const int POLYNOMIAL_B = 1;

	int m_tmp_parm_val; // tmp variable
	int m_tmp_parm_key; // tmp variable
	int m_tmp_k;
	std::string m_tmp_parm_object; // tmp variable

	std::map<int,int > m_a_parameters;	// config - container for a - parameters
	std::map<int,int > m_b_parameters;	// config - container for b - parameters
	int	m_stationary;	// config - stationary or not
	int m_k;	// config - k (delay)
	std::string m_object_name;	// config - object name

	bool m_config_loaded;	// config flag

	// ------------------------------------------------------------------------------

	private:
		Config(void) {};		// disable constructor
		Config (const Config &);		// disable default copy
		Config & operator = (const Config &);		// disable default copy
		void clear(void);		// clear variables


	public:
		~Config(void) {}		// destructor

		bool check_if_config_loaded(void) { return this->m_config_loaded; };		// check if config was loaded properly
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

		// Instance of object
		static Config & getInstance()
		{
			static Config instance; 
			return instance; 	
		};		

};

#endif