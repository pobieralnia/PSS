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
		std::deque<int> m_simulation_step_counter;
		std::vector<double> m_outputs_vector;
		std::vector<double> m_errors_vector;

	public:
		Loop(void);
		~Loop(void);
		void Loop::set_regulator(Regulator * regulator);
		void Loop::set_object(Object * arx);
		double simulation_step();
		void get_outputs(std::deque<double> & out);
		void get_outputs(std::vector<double> & out);
		void get_errors(std::vector<double> & err);
		std::deque<int>	get_simulation_step(void);
};

#endif

