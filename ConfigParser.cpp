// ---------------------------------------------------------------------------------
// Filename:	ConfigParser.cpp
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ConfigParser
// ---------------------------------------------------------------------------------

#include "stdafx.h"
#include "ConfigParser.h"
#include <regex>
#include <string>

/**
 * Parse line to load b - parameter
 *
 * @param:		string line
 * @param:		int b_value
 * @param:		int b_key
 * @return:		bool - True for success ? False if fail
 */
bool ConfigParser::regex_b_parameter(std::string line, int * b_val, int * b_key)
{
    std::tr1::cmatch res;
    std::tr1::regex rx("b_parametr=([^<]+)&([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "" && res[2] != "")
		{
			std::string b = res[1];
			std::string c = res[2];
			* b_val =  atoi(b.c_str());
			* b_key =  atoi(c.c_str());

			return true; // success
		}
		
	}

	return false; // fail

}

/**
 * Parse line to load a - parameter
 *
 * @param:		string line
 * @param:		int a_val
 * @param:		int a_key
 * @return:		bool - True for success ? False if fail
 */
bool ConfigParser::regex_a_parameter(std::string line, int * a_val, int * a_key)
{
    std::tr1::cmatch res;
    std::tr1::regex rx("a_parametr=([^<]+)&([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "" && res[2] != "")
		{
			std::string a = res[1];
			std::string b = res[2];
			* a_val = atoi(a.c_str());
			* a_key = atoi(b.c_str()); 
			
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
    std::tr1::regex rx("stationary=([^<]+);");
    if( std::tr1::regex_search(line.c_str(), res, rx) )
	{
		if(res[1] != "")
		{
			std::string b = res[1];
			return  atoi(b.c_str()) & 1;
		}
		
	}
	
	return false; // fail
}