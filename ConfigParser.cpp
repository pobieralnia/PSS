// ---------------------------------------------------------------------------------
// Filename:	ConfigParser.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ConfigParser
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include "ConfigParser.h"

#include <regex>
#include <sstream>
#include <cstdlib>
#include <string>

/**
 * Parse line to load b - parameter
 *
 * @param:		string line
 * @param:		int b_value
 * @param:		int b_key
 * @return:		bool - True for success ? False if fail
 */
bool ConfigParser::regex_b_parameter(std::string line, double * b_val, int * b_key)
{
    std::tr1::cmatch res;
    std::tr1::regex rx("b=([0-9]+)&([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "" && res[2] != "")
		{
			std::istringstream s_val(res[2]);
			s_val >> * b_val;

			std::istringstream s_key(res[1]);
			s_key >> * b_key;

			return true; // success
		}
		
	}

	return false; // fail

}

/**
 * Parse line to load b - parameter
 *
 * @param:		string line
 * @return:		bool
 */
bool ConfigParser::regex_end_of_config(std::string line)
{
    std::tr1::cmatch res;
    std::tr1::regex rx("END-([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] == "CONFIG")
		{
			return true;
		}
	}

	return false;
}

/**
 * Parse line to load a - parameter
 *
 * @param:		string line
 * @param:		double a_val
 * @param:		double a_key
 * @return:		bool - True for success ? False if fail
 */
bool ConfigParser::regex_a_parameter(std::string line, double * a_val, int * a_key)
{
    std::tr1::cmatch res;
    std::tr1::regex rx("a=([0-9]+)&([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "" && res[2] != "")
		{
			std::istringstream s_val(res[2]);
			s_val >> * a_val;

			std::istringstream s_key(res[1]);
			s_key >> * a_key;
			return true; // success
			
		}
		
	}
	
	return false; // fail
}

/**
 * Parse line to load k - parameter
 *
 * @param:		string line
 * @param:		double k
 * @return:		bool - True for success ? False if fail
 */
bool ConfigParser::regex_k(std::string line, double * k)
{
    std::tr1::cmatch res;
    std::tr1::regex rx("k=([0-9]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "")
		{
			std::istringstream stm(res[1]);
			stm >> * k;
			
			return true; // success
		}
	}
	
	return false; // fail
}

/**
 * Parse lines to load stationary variable / parameter
 *
 * @param:		string line
 * @return:		bool - True for success ? False if fail
 */
bool ConfigParser::regex_stationary(std::string line)
{
    std::tr1::cmatch res;
	std::tr1::regex rx("stationary=([0-1]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "")
		{
			std::string b = res[1];
			return  atoi(b.c_str()) && 1;
		}
	}
	
	return false; // fail
}

/**
 * Get da parameters
 *
 * @param		string line
 * @return		bool - True for success
 */
bool ConfigParser::regex_da(std::string line, int * da)
{
	std::tr1::cmatch res;
	std::tr1::regex rx("da=([0-9]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "")
		{
			std::istringstream s_da(res[1]);
			s_da >> * da;
			return true; // success
			
		}
	}
	
	return false; // fail
}

/**
 * Get da parameters
 *
 * @param		string line
 * @return		bool - True for success
 */
bool ConfigParser::regex_db(std::string line, int * db)
{
	std::tr1::cmatch res;
	std::tr1::regex rx("db=([0-9]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "")
		{
			std::istringstream s_da(res[1]);
			s_da >> * db;
			return true; // success
			
		}
	}
	
	return false; // fail
}

/**
 * Get noise parameter
 *
 * @param		string line
 * @return		bool - True for success
 */
bool ConfigParser::regex_noise(std::string line, double * noise)
{
	double val;

	std::tr1::cmatch res;
	std::tr1::regex rx("noise=([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "")
		{
			std::istringstream s_noise(res[1]);
			s_noise >> val;
			if(val > 0.0)
			{
				* noise = val;
				return true; // success
			}
		}
	}
	
	return false; // fail
}

/**
 * Fill parameters for generator
 *
 * @param		string line
 * @param		map<string,double> & parm
 * @return		void
 */
void ConfigParser::regex_generator_parameter(std::string line, std::map<std::string, double> & parm)
{
	double val;
	std::string name;

	std::tr1::cmatch res;
	std::tr1::regex rx("param=([^<]+)&([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "" && res[2] != "")
		{
			std::string name = res[1];
			std::istringstream s_val(res[2]);
			s_val >> val;
			if(val > 0.0)	parm[name] = val;
			
		}
	}
}

/**
 * Fill parameters for regulator
 *
 * @param		string line
 * @param		map<string,double> & parm
 * @return		void
 */
void ConfigParser::regex_regulator_parameter(std::string line, std::map<std::string, double> & parm)
{
	double val;
	std::string name;

	std::tr1::cmatch res;
	std::tr1::regex rx("param=([^<]+)&([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "" && res[2] != "")
		{
			std::string name = res[1];
			std::istringstream s_val(res[2]);
			s_val >> val;
			if(val > 0.0)	parm[name] = val;
		}
	}
}