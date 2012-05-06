// ---------------------------------------------------------------------------------
// Filename:	Loop.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		Loop
// ---------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Loop.h"
#include <iostream>

/**
 * Constructor
 *
 * @param	Object * regulator
 */
Loop::Loop(Object * arx) : m_REGULATOR(NULL), m_ARX(arx)
{
	this->m_outputs.clear();
	this->m_simulation_step_counter.clear();
	this->m_outputs.push_front(0.0);
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
void Loop::set_regulator(Object * regulator)
{
	m_REGULATOR = regulator;
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

	if(!m_outputs.empty())
	{
		input = m_outputs.front();
	}

	if(m_REGULATOR)
		u = m_REGULATOR->simulate(input);
	else
		u = input; // TODO pure regulator w - y

	const double y = m_ARX->simulate(u);

	this->m_outputs.push_front(y);
	this->m_simulation_step_counter.push_front(this->m_simulation_step_counter.back() + 1);

	return y;
}

/**
 * Get all outputs
 *
 * @return	std::deque<double>
 */
std::deque<double> Loop::get_outputs(void)
{
	return m_outputs;
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

