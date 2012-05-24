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
RegulatorP::RegulatorP(void) : m_w(0.0), m_e(0.0), m_k(0.0), m_proces(NULL)
{
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
		m_w = m_proces->simulate();

		m_e = m_w - input;

		return m_e * m_k;
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
	return m_e; 
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