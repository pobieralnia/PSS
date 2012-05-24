// ---------------------------------------------------------------------------------
// Filename:	Loop.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		Loop
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Loop.h"
#include <algorithm>
#include <iterator>
/**
 * Constructor
 *
 * @param	Object * regulator
 */
Loop::Loop(void) : m_REGULATOR(NULL), m_ARX(NULL), m_e(0.0)
{
	m_outputs.push_back(0.0);

	m_outputs_vector.push_back(0.0);
	m_simulation_step_counter.push_back(0.0);
}

/**
 * Destructor
 * 
 * @return	void
 */
Loop::~Loop(void)
{
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
	double u = 0.0;

	const double input = m_outputs.front();

	m_outputs.pop_back();

	if(m_REGULATOR)
	{
		u = m_REGULATOR->simulate(input);
		m_e = m_REGULATOR->get_error();
	}
	else
		u = input; // TODO pure regulator w - y

	const double y = m_ARX->simulate(u);

//	m_outputs.push_back(y);
	m_outputs.push_front(y);
	
	//m_errors_vector.push_back(e);

	//m_simulation_step_counter.push_back(m_simulation_step_counter.back() + 1);

	return y;
}
double Loop::get_error()
{
	return m_e;
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
//	for(auto ite = m_outputs.rbegin() ; ite != m_outputs.rend() ; ite ++)
//	{
	//	out.push_back(*ite);
	//}
	//std::reverse(out.begin(),out.end());     

	//out.reserve(6);
	//std::copy(m_outputs.rbegin(), m_outputs.rend(), std::inserter(out, out.begin()));

	//for(auto ite = m_outputs.rbegin() ; ite != m_outputs.rend() ; ite ++)
	//{
	//	out.push_back(*ite);
	//}
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

int Loop::get_current_simulation_step(void)
{
	return m_simulation_step_counter.back();
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

