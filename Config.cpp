// ---------------------------------------------------------------------------------
// Filename:	Config.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include "Config.h"

/**
 * Get flag - get flag for object,generator,regulator config status, if loaded properly.
 * Default it returns object config status flag.
 *
 * @param		enum ConfigType cty
 * @return		bool
 */
bool Config::get_flag(ConfigType cty)
{
	switch (cty)
	{
		case OBJECT:
			return this->m_config_object_loaded;
			break;
		case REGULATOR:
			return this->m_config_regulator_loaded;
			break;
		case GENERATOR:
			return this->m_config_generator_loaded;
			break;
		default:
			return	this->m_config_object_loaded;
	}
}

/**
 * Set config to true
 * 
 * @param		enum ConfigType cty
 * @return		void
 */
void Config::set_config(ConfigType cty)
{
	switch (cty)
	{
		case OBJECT:
			this->m_config_object_loaded = true;
			break;
		case REGULATOR:
			this->m_config_regulator_loaded = true;
			break;
		case GENERATOR:
			this->m_config_generator_loaded = true;
			break;
		default:
			this->m_config_object_loaded = true;
			break;
	}
}

/**
 * Clear flag
 *
 * @param		enum ConfigType cty
 * @return		void
 */
void Config::clear_flag(ConfigType cty)
{
	switch (cty)
	{
		case OBJECT:
			this->m_config_object_loaded = false;
			break;
		case REGULATOR:
			this->m_config_regulator_loaded = false;
			break;
		case GENERATOR:
			this->m_config_generator_loaded = false;
			break;
		default:
			this->m_config_object_loaded = false;
			break;
	}
}

/**
 * Clear all flags
 *
 * @return		void
 */
void Config::clear_flag()
{
	this->m_config_object_loaded = false;
	this->m_config_regulator_loaded = false;
	this->m_config_generator_loaded = false;
}

/**
 * Get config for object
 *
 * @param		std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>> conf
 * @param		int unsigned i
 * @return		void
 */
void Config::get_config(std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>> & conf, int unsigned i)
{
	if( this->structo.m_vector_objects.size() > 0 && i <= this->structo.m_vector_objects.size())
	{
		conf = this->structo.m_vector_objects[i];
	}
};

/**
 * Get config for generator
 *
 * @param		std::vector<std::map<std::string,double>> & conf
 * @return		void
 */
void Config::get_config_generator(std::vector<std::map<std::string,double>> & conf)
{
	if( this->structo.m_vector_generator.size() > 0)
	{
		conf = this->structo.m_vector_generator;
	}
};

/**
 * Get config for regulator
 *
 * @param		std::map<std::string,double> conf
 * @param		int unsigned i
 * @return		void
 */
void Config::get_config_regulator(std::map<std::string,double> & conf, int unsigned i)
{
	if( this->structo.m_vector_regulator.size() > 0 && i <= this->structo.m_vector_regulator.size())
	{
		conf = this->structo.m_vector_regulator[i];
	}
};