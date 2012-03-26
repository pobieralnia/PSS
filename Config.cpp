// ---------------------------------------------------------------------------------
// Filename:	Config.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config,ConfigParser
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include <string>
#include <tuple>
#include <sstream>
#include "Config.h"


/**
 * Init - filled main variables with default data
 *
 * @return		void
 */
void Config::clear(void)
{
	this->m_b_parameters_counter = 0;
	this->m_a_parameters_counter = 0;
	this->m_object_parameters_counter = 0;
	this->m_stationary = 0;
	this->m_a_parameters.clear();
	this->m_b_parameters.clear();
}

/**
 * Clear config vector
 *
 * @return		void
 */
void Config::clear_vector_config()
{
	this->clear();
	this->m_config_loaded = false;
	this->m_vector_configs.clear();
}

/**
 * Set new config - config have never been used, addtionaly main variables are cleared
 *
 * @return		void
 */
void Config::set_config(void)
{
	this->m_config_loaded = true;
}

/**
 * Parse lines to load all main variables in config file
 *
 * @param		string line
 * @return		void
 */
void Config::parse_file(std::string line)
{

	// check if not empty
	if(!line.empty())
	{
		// Clean values
		m_tmp_parm_val = 0;
		m_tmp_parm_key = 0;
		m_tmp_parm_object.clear();

		// Check what kind of variables are in the line
		if(ConfigParser::regex_a_parameter(line, &m_tmp_parm_val, &m_tmp_parm_key))
		{
			this->m_a_parameters[m_tmp_parm_key] = m_tmp_parm_val;
			this->m_a_parameters_counter++;
		}
		else if(ConfigParser::regex_b_parameter(line, &m_tmp_parm_val, &m_tmp_parm_key))
		{
			this->m_b_parameters[m_tmp_parm_key] = m_tmp_parm_val; // number
			this->m_b_parameters_counter++;
		}
		else if(ConfigParser::regex_stationary(line))
		{
			this->m_stationary = 1;
		}
		else if(ConfigParser::regex_object_name(line, m_tmp_parm_object))
		{
			this->m_object_name = m_tmp_parm_object;
			this->m_object_parameters_counter++;
		}
		else if(ConfigParser::regex_end_of_config(line))
		{
			 // initialize a tuple and put in vector of configs
			 m_vector_configs.push_back(make_tuple(this->m_object_name, this->m_b_parameters, this->m_a_parameters));

			 // clear main variables
			 this->clear();
		}
	}
}

/**
 * Get the string value of the amount of a parameters
 *
 * @param		int i - flag
 * @return		string
 */
std::string Config::check_value_of_a_parm(int i)
{
	std::stringstream ss; //create a stringstream
	ss << this->m_a_parameters_counter;
	return ss.str(); //return a string with the contents of the stream
}

/**
 * Get the string value of the amount of b parameters
 *
 * @param		int i - flag
 * @return		string
 */
std::string Config::check_value_of_b_parm(int i)
{
	std::stringstream ss; //create a stringstream
	ss << this->m_b_parameters_counter;
	return ss.str(); //return a string with the contents of the stream
}

/**
 * Get the string value of the stationary parametr
 *
 * @param		int i - flag
 * @return		string
 */
std::string Config::get_object_name_counter(int i)
{
	std::stringstream ss; //create a stringstream
	ss << this->m_object_parameters_counter;
	return ss.str(); //return a string with the contents of the stream
}