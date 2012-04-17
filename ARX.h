// ---------------------------------------------------------------------------------
// Filename:	ARX.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ARX	
// ---------------------------------------------------------------------------------

#ifndef __ARX_H__
#define __ARX_H__

#include <deque>
#include <string>

/**
 * @class		ARX ARX.h
 * @brief		Class which simulate object ARX
 * 
 * Two contructors default and loaded with initial data.
 */
class ARX
{
	std::string m_object_name;	// name of the object
	std::deque<double> m_U;		// container for inputs
	std::deque<double> m_Y;		// container for outputs
	std::deque<double> m_A;		// container for A polynomial
	std::deque<double> m_B;		// container for B polynomial
	int m_delay;		// delay
	int m_stat;		// stationary
	static const int m_noise = 1;

	public:
		ARX() {};
		//ARX(const std::string & name, std::deque<double> A, std::deque<double> B, int delay, int stat) : m_object_name(name), m_A(A), m_B(B), m_delay(delay), m_stat(stat) { this->update_sample_size(); };
		void get_parameters(const std::string & name, std::deque<double> A, std::deque<double> B, int delay, int stat)
		{
			m_object_name = name;
			m_A = A;
			m_B = B;
			m_delay = delay;
			m_stat = stat;
			this->update_sample_size();
		}
		double simulate(double input);
		virtual ~ARX(void) {};

		void set_initial_state(const std::deque<double> u_init, const std::deque<double> y_init);
	
	private:
		void update_sample_size();
};
 
#endif
