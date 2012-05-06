// ---------------------------------------------------------------------------------
// Filename:	RegulatorPID.cpp
// Author:		Tomasz L.
// Date:		2012-05-02
// Package:		Regulator
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "RegulatorPID.h"

/**
 * Constructor - set initial variables
 *
 * @return		void
 */
RegulatorPID::RegulatorPID(void) : m_Tp(1), m_b(1), m_k(1), m_Ti(2), m_e(0), m_N(1), m_Td(1), m_w(0)
{
	m_history_Y.push_front(0.0);
	m_history_U.push_front(0.0);
	m_history_Integral.push_front(0.0);
	m_history_Proportional.push_front(0.0);
	m_history_Differential.push_front(0.0);
	m_proces = NULL;
}

/**
 * Destructor
 *
 * @return		void
 */
RegulatorPID::~RegulatorPID(void)
{
}

/**
 * Clone regulator
 *
 * @return new RegulatorP
 */
RegulatorPID * RegulatorPID::clone () const
{
    return new RegulatorPID(*this);
}

/**
 * Simulate
 * 
 * @param		double input
 * @return		double u - control signal
 */
double RegulatorPID::simulate(double input)
{
	if(m_proces)
	{
		m_w = m_proces->simulate();
		m_e = m_w -  m_history_Y.front();
		m_history_E.push_front(m_e);

		const double p = proportional(m_w, input);
		const double i = integral(m_e);
		const double d = differential(input, m_history_Y.front());
		const double u = i + p + d;

		m_history_Proportional.push_front(p);
		m_history_Integral.push_front(i);
		m_history_Differential.push_front(d);
		m_history_U.push_front(u);
		m_history_Y.push_front(input);

		return u;
	}
	else
	{
		return 0.0;
	}
}

/**
 * Proportional part of Regaultor PID
 *
 * @param		double w set point
 * @param		double y last output
 * @return		double
 */
double RegulatorPID::proportional(double w, double y)
{
	return m_k * (m_b * w - y);
}

/**
 * Integral part of Regulator PID
 *
 * @param		double e - deviation
 * @return		double
 */
double RegulatorPID::integral(double e)
{
	return m_history_Integral.front() + ( (m_k * m_Tp * e) / m_Ti );
}

/**
 * Differential part of Regulator PID
 *
 * @param		double y
 * @param		double previous_y
 * @return		double
 */
double RegulatorPID::differential(double y, double previous_y)
{
	return ( m_Td / (m_Td + m_N * m_Tp) ) * m_history_Differential.front() - m_k * ( (m_N * m_Td) / (m_Td + m_N * m_Tp) ) * (y - previous_y);
}

/**
 * Set parameters for Regulator
 *
 * @param		std::map<std::string, double> parm
 * @return		void
 */
void RegulatorPID::set_parameters(std::map<std::string, double> & parm)
{
	// Clear all tmp values
	m_tmp_parameter.clear();

	m_tmp_parameter["k"] = parm["k"];
	m_tmp_parameter["Td"] = parm["k"];
	m_tmp_parameter["N"] = parm["k"];
	m_tmp_parameter["Tp"] = parm["k"];
	m_tmp_parameter["b"] = parm["k"];
	m_tmp_parameter["Ti"] = parm["k"];

	// Check parameters if they are correct
	try
	{
		if(check_parameters())
		{
			m_k = parm["k"];
			m_Td = parm["Td"];
			m_N = parm["N"];
			m_Tp = parm["Tp"];
			m_b = parm["b"];
			m_Ti = parm["Ti"];
		}
	}
	catch (std::string & e)
	{
		throw; // rethrow exception
	}
}

/**
 * Set one parameter for Regulator
 *
 * @param		const std::string & param_name
 * @param		double value
 * @return		void
 */
void RegulatorPID::set_parameters(const std::string & param_name, double value)
{
	// Clear all tmp values
	m_tmp_parameter.clear();

	if(param_name == "k")
		m_tmp_parameter["k"] = value;
	else if(param_name == "Td")
		m_tmp_parameter["Td"] = value;
	else if(param_name == "N")
		m_tmp_parameter["N"] = value;
	else if(param_name == "Tp")
		m_tmp_parameter["Tp"] = value;
	else if(param_name == "b")
		m_tmp_parameter["b"] = value;
	else if(param_name == "Ti")
		m_tmp_parameter["Ti"] = value;

	// Check parameters if they are correct
	try
	{
		if(check_parameters())
		{
			// TODO Bezsens nie mam pomys³u jak tego nie dublowac
			if(param_name == "k")
				m_k = value;
			else if(param_name == "Td")
				m_Td = value;
			else if(param_name == "N")
				m_N = value;
			else if(param_name == "Tp")
				m_Tp = value;
			else if(param_name == "b")
				m_b = value;
			else if(param_name == "Ti")
				m_Ti = value;
		}
	}
	catch (std::string & e)
	{
		throw; // rethrow exception
	}
}

/**
 * Get parameters from Regulator
 *
 * @param		std::map<std::string, double> parm
 * @return		void
 */
void RegulatorPID::get_parameters(std::map<std::string, double> & parm) const
{
	parm["k"] = m_k;
    parm["Td"] =  m_Td;
    parm["N"] = m_N;
    parm["Tp"] = m_Tp;
    parm["b"] = m_b;
	parm["Ti"] = m_Ti;
}

/** 
 * Get error for current simulation regulation
 *
 * @return	double
 */
double RegulatorPID::get_error()
{
	return m_history_E.front();
}

/**
 * Get set point value
 *
 * @return		double
 */
double RegulatorPID::get_setpoint()
{
	return m_w;
}

/**
 * Set setpoint
 *
 * @param		SignalBase * proces - signal generator
 * @return		void
 */
void RegulatorPID::set_setpoint(SignalBase * proces)
{
	m_proces = proces;
}

/**
 * Check parameters if they are correct with model
 *
 * @return		bool
 */
bool RegulatorPID::check_parameters()
{
	// All parameters have to be positive 
	for(std::map<std::string,double>::iterator itr = m_tmp_parameter.begin(); itr != m_tmp_parameter.end(); itr++)
	{
		if(itr->second < 0)
		{
			throw std::string("Parametry musz¹ byæ dodatnie");
			return false;
		}
	}

	double td = 0.0;
	double n = 0.0;
	double tp = 0.0;

	if(m_tmp_parameter.find("Td") != m_tmp_parameter.end())
		td = m_tmp_parameter["Td"];
	else
		td = m_Td;

	if(m_tmp_parameter.find("Tp") != m_tmp_parameter.end())
		tp = m_tmp_parameter["Tp"];
	else
		tp = m_Tp;

	if(m_tmp_parameter.find("N") != m_tmp_parameter.end())
		n = m_tmp_parameter["N"];
	else
		n = m_N;

	if(td <= (n * tp)/2)
	{
		throw std::string("B³¹d modu³u");
		return false;
	}

	return true;
}