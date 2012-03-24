// ---------------------------------------------------------------------------------
// Filename:	Config.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config,ConfigParser
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include <string>
#include <stdlib.h>
#include "Config.h"


/**
 * Init - filled main variables with default data
 *
 * @return:		void
 */
void Config::init(void)
{
	this->m_b_parameters_counter = 0;
	this->m_a_parameters_counter = 0;
	this->m_stationary = 0;
	this->m_a_parameters.clear();
	this->m_b_parameters.clear();
}

/**
 * Set new config - config have never been used, addtionaly main variables are cleared
 *
 * @return:		void
 */
void Config::set_new_config(void)
{
	this->init(); // clear all
	this->m_new_config = true;
}

/**
 * Disable new config - config now, was used
 *
 * @return:		void
 */
void Config::disable_new_config(void)
{
	// todo
	// copy config
	this->m_new_config = false;
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

	}
}

/**
 * Get the string value of the amount of a parameters
 *
 * @param:		int i - flag
 * @return:		string
 */
std::string Config::check_value_of_a_parm(int i)
{
	std::string tmp;
	itoa(this->m_a_parameters_counter, (char*)tmp.c_str(), 10);
	return tmp.c_str();
}

/**
 * Get the string value of the amount of b parameters
 *
 * @param:		int i - flag
 * @return:		string
 */
std::string Config::check_value_of_b_parm(int i)
{
	std::string tmp;
	itoa(this->m_b_parameters_counter, (char*)tmp.c_str(), 10);
	return tmp.c_str();
}

/**
 * Get the string value of the stationary parametr
 *
 * @param:		int i - flag
 * @return:		string
 */
std::string Config::check_if_stationary_parm(int i)
{
	std::string tmp;
	itoa(this->m_stationary, (char*)tmp.c_str(), 10);
	return tmp.c_str();
}