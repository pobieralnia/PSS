// ---------------------------------------------------------------------------------
// Filename:	Config.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Config
// ---------------------------------------------------------------------------------

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>

#include "ConfigObject.h"
#include "ConfigGenerator.h"
#include "ConfigRegulator.h"
#include "ConfigStruct.h"

class ConfigBase; // forward declaration (ConfigObject)

/**
 * @class		Config Config.h
 * @brief		Main class for keeping settings inside containers and variables
 *
 * It inherit from ConfigParser class where are stored methods for parsing values from string line. The main variables are k, polyniomal A,B, stationarity, object name.
 *
 * Simply usage:
 * Config::getInstance().clear_all();	
 * Config::getInstance().set_config();
 */
class Config : someStruct
{
	bool m_config_object_loaded;	// object config flag
	bool m_config_generator_loaded;	// generator config flag
	bool m_config_regulator_loaded;	// regulator config flag

	struct someStruct structo;

	private:
		Config(void){ this->clear_flag(); };		// disable constructor
		Config (const Config &);		// disable default copy
		Config & operator = (const Config &);		// disable default copy

	public:
		~Config(void) {}		// destructor

		std::vector<double> m_ARX;
		std::vector<double> m_ARXe;

		// Interface
		enum ConfigType
		{
			OBJECT = 0,
			REGULATOR = 1,
			GENERATOR = 2
		};

		bool get_flag(ConfigType cty);		// get flag status
		void set_config(ConfigType cty);	// set exact config flag to true
		void clear_flag(ConfigType cty);	// clear flag for exact config
		void clear_flag();					// clear all flags

		template<typename T>
		void get_config(T & conf, ConfigType cty)
		{
			if( this->structo.m_vector_objects.size() > 0 )
			{
				if(cty == OBJECT)
				{
					conf = this->structo.m_vector_objects;
				}
			}
		};

		template<typename T>
		void get_configg(T & conf)
		{
			conf = this->structo.m_vector_generator;
		};

		// ------------------------------------------------------------------------------

		// Instance of object
		static Config & getInstance()
		{
			static Config instance; 
			return instance; 	
		};
		
		// Create static driver
		ConfigBase * create(std::string type) {
			if ( type == "object" ) return new ConfigObject(&structo);
			else if ( type == "generator" ) return new ConfigGenerator(structo);
			else if ( type == "regulator" ) return new ConfigRegulator(structo);
			return NULL;
		};
		
};

#endif