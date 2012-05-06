// ---------------------------------------------------------------------------------
// Filename:	ARX.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		ARX	
// ---------------------------------------------------------------------------------

#ifndef __ARX_H__
#define __ARX_H__

#include "Object.h"

#include <deque>
#include <string>
#include <map>

/**
 * @class		ARX ARX.h
 * @brief		Class which simulate object ARX
 * 
 * Two contructors default and loaded with initial data.
 */
class ARX : public Object
{
	std::deque<double> m_U;		// container for inputs
	std::deque<double> m_Y;		// container for outputs
	std::deque<double> m_A;		// container for A polynomial
	std::deque<double> m_B;		// container for B polynomial
	int m_delay;	// delay
	int m_stat;		// stationary
	int m_noise;	// noise

	public:
		ARX();
		virtual ~ARX(void) {};
		void set_parameters(std::deque<double> A, std::deque<double> B, std::map<std::string, double> others);
		void get_parameters(std::deque<double> & A, std::deque<double> & B, std::map<std::string, double> & others) const;
		void clear(void);
		double simulate(double input);
		void set_initial_state(const std::deque<double> u_init, const std::deque<double> y_init);
	
	private:
		void update_sample_size();
};
 
#endif