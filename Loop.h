#ifndef __LOOP_H__
#define __LOOP_H__

#include "Object.h"
#include <deque>

/**
 * @class	Loop Loop.h
 * @brief	Regulation loop
 * 
 * Simulate regulator with object, regulator is passed by pointer
 */
class Loop
{
	private:
		Object * m_REGULATOR;
		Object * m_ARX;
		std::deque<double> m_outputs;
		std::deque<int> m_simulation_step_counter;

	public:
		Loop(Object * arx);
		~Loop(void);
		void Loop::set_regulator(Object * regulator);
		double simulation_step();
		std::deque<double> get_outputs(void);
		std::deque<int>	get_simulation_step(void);
};

#endif

