#ifndef __LOOP_H__
#define __LOOP_H__

#include "Object.h"
#include "Regulator.h"
#include <deque>
#include <vector>

/**
 * @class	Loop Loop.h
 * @brief	Regulation loop
 * 
 * Simulate regulator with object, regulator is passed by pointer
 */
class Loop
{
	private:
		Regulator * m_REGULATOR;
		Object * m_ARX;
		std::deque<double> m_outputs;
		int m_simulation_step_counter;
		double m_e;
	public:
		Loop(void);
		~Loop(void);
		void Loop::set_regulator(Regulator * regulator);
		void Loop::set_object(Object * arx);
		double simulation_step();
		double get_error();
		double get_setpoint(void) const;
		int get_current_simulation_step(void) const;
};

#endif

