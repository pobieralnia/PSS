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
class Config : ConfigStruct
{
	private:
		bool m_config_object_loaded;	/*< object config flag */
		bool m_config_generator_loaded;	/*< generator config flag */
		bool m_config_regulator_loaded;	/*< regulator config flag */

		// Interface
		enum ConfigType
		{
			OBJECT = 0,
			REGULATOR = 1,
			GENERATOR = 2
		};

		struct ConfigStruct structo;

	private:
		Config(void){ this->clear_flag(); };		// disable constructor
		Config (const Config &);		// disable default copy
		Config & operator = (const Config &);		// disable default copy

	public:
		~Config(void) {}		// destructor

		bool get_flag(ConfigType cty);		// get flag status
		void set_config(ConfigType cty);	// set exact config flag to true
		void clear_flag(ConfigType cty);	// clear flag for exact config
		void clear_flag();					// clear all flags
		void get_config(std::tuple <std::map<int,double>, std::map<int,double>, std::map<std::string, double>> & conf, int unsigned i);
		void get_config_generator(std::vector<std::map<std::string,double>> & conf);
		void get_config_regulator(std::map<std::string,double> & conf, int unsigned i);


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