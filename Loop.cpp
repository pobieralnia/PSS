// ---------------------------------------------------------------------------------
// Filename:	Loop.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		Loop
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Loop.h"

/**
 * Constructor
 *
 * @param	Object * regulator
 */
Loop::Loop(void) : m_REGULATOR(NULL), m_ARX(NULL)
{
	this->m_outputs.clear();
	this->m_simulation_step_counter.clear();
	this->m_outputs.push_back(0.0);
	this->m_simulation_step_counter.push_back(0.0);
}

/**
 * Destructor
 * 
 * @return	void
 */
Loop::~Loop(void)
{
	m_REGULATOR = NULL;
	m_ARX = NULL;

	delete m_REGULATOR;
	delete m_ARX;
}

/**
 * Set regulator
 *
 * @param	Object * regulator
 * @return	void
 */
void Loop::set_regulator(Regulator * regulator)
{
	m_REGULATOR = regulator;
}

/**
 * Set Object
 *
 * @param	Object * object
 * @return	void
 */
void Loop::set_object(Object * arx)
{
	m_ARX = arx;
}


/**
 * Simulation step - generate simulation and return value
 *
 * @return	double y - output of loop simulation
 */
double Loop::simulation_step()
{
	double input = 0.0;
	double u = 0.0;
	double e = 0.0;

	if(!m_outputs.empty())
	{
		input = m_outputs.back();
	}

	if(m_REGULATOR)
	{
		u = m_REGULATOR->simulate(input);
		e = m_REGULATOR->get_error();
	}
	else
		u = input; // TODO pure regulator w - y

	const double y = m_ARX->simulate(u);

	m_outputs.push_back(y);
	m_outputs_vector.push_back(y);
	m_errors_vector.push_back(e);
	m_simulation_step_counter.push_back(this->m_simulation_step_counter.back() + 1);

	return y;
}

/**
 * Get all outputs
 *
 * @return	std::deque<double>
 */
void Loop::get_outputs(std::deque<double> & out)
{
	out = m_outputs;
}

/**
 * Get all outputs
 *
 * @return	std::deque<double>
 */
void Loop::get_outputs(std::vector<double> & out)
{
	out = m_outputs_vector;
}

/**
 * Get all outputs
 *
 * @return	std::deque<double>
 */
void Loop::get_errors(std::vector<double> & err)
{
	err = m_errors_vector;
}

/**
 * Get simulation step
 *
 * @return	std::deque<int>
 */
std::deque<int> Loop::get_simulation_step(void)
{
	return m_simulation_step_counter;
}

