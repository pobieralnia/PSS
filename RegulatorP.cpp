// ---------------------------------------------------------------------------------
// Filename:	Regulator.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		RegulatorP
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "RegulatorP.h"
#include <iostream>

/**
 * Constructor - set initial parameters
 *
 * @return		void
 */
RegulatorP::RegulatorP(void)
{
	m_proces = NULL;
	m_k = 1;
	m_w = 0;

	m_history_E.clear();
	m_history_U.clear();
	m_history_Y.clear();

	m_history_U.push_front(0);
	m_history_E.push_front(0);
    m_history_Y.push_front(0);
}

/**
 * Destructor
 *
 * @return		void
 */
RegulatorP::~RegulatorP(void)
{
}

/**
 * Clone regulator
 *
 * @return new RegulatorP
 */
RegulatorP * RegulatorP::clone () const
{
    return new RegulatorP(*this);
}

/**
 * Set parameters for Regulator
 *
 * @param		std::map<std::string, double> parm
 * @return		void
 */
void RegulatorP::set_parameters(std::map<std::string, double> & parm)
{
	m_k = parm["k"];
}

/**
 * Set one parameter for Regulator
 *
 * @param		const std::string & param_name
 * @param		double value
 * @return		void
 */
void RegulatorP::set_parameters(const std::string & param_name, double value)
{
	if(param_name == "k")
		m_k = value;
}

/**
 * Get parameters from Regulator
 *
 * @param		std::map<std::string, double> parm
 * @return		void
 */
void RegulatorP::get_parameters(std::map<std::string, double> & parm) const
{
	parm["k"] = m_k;
}

/**
 * Simulate
 * 
 * @param		double input
 * @return		double u
 */
double RegulatorP::simulate(double input)
{
	if(m_proces)
	{
		const double w = m_proces->simulate();
		m_w = w;

		m_history_Y.push_front(input);
		const double e = m_w - input;
		const double u = e * m_k;

		m_history_E.push_front(e);
		m_history_U.push_front(u);

		return u;
	}
	else
	{
		return 0.0;
	}
}

/** 
 * Get error for current simulation regulation
 *
 * @return	double
 */
double RegulatorP::get_error()
{
	return m_history_E.front(); 
}

/** 
 * Get error for all simulation steps
 *
 * @return	double
 */
void RegulatorP::get_error(std::vector<double> & err)
{
	std::vector<double> v;
	for(auto it =  m_history_E.rbegin(); it != m_history_E.rend() ; it++)
		v.push_back(*it);
	
	err = v;
}

/**
 * Get set point value
 *
 * @return		double
 */
double RegulatorP::get_setpoint()
{
	return m_w;

}

/**
 * Set setpoint
 *
 * @param		SignalBase * proces - signal generator
 * @return		void
 */
void RegulatorP::set_setpoint(SignalBase * proces)
{
	m_proces = proces;
}