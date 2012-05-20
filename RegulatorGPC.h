// ---------------------------------------------------------------------------------
// Filename:	RegulatorGPC.h
// Author:		Tomasz L.
// Date:		2012-05-03
// Package:		Regulator
// ---------------------------------------------------------------------------------

#ifndef __REGULATORGPC_H__
#define __REGULATORGPC_H__

#include "Regulator.h"
#include "Signal.h"
#include "Identification.h"
#include <deque>
#include <vector>

/**
 * @class	RegulatorGPC	RegulatorGPC.h
 * @brief	Class for simulating GPC regulator (Generalized Predictive Control)
 *
 * Class use Identification for getting ARX polynomials
 *
 * Exceptions:
 * @see		set_parameters(const std::string & param_name, double value)
 * @see		set_parameters(std::map<std::string, double> & parm)
 */
class RegulatorGPC : public Regulator
{
	private:
		// GPC parameters
		int m_H, m_L;
		double m_alpha, m_ro, m_w;
		int m_initial_steps;
		int m_initial_steps_left;
		std::deque<double> m_history_U, m_history_Y, m_history_E, m_history_DU;
		std::deque<double> m_poly_A;		// container for A polynomial
		std::deque<double> m_poly_B;		// container for B polynomial
		std::map<std::string, double> m_tmp_parameter;

		// Parameters for identification
		int m_rankA,m_rankB;
		double m_lambda;

		// Signal Proces Gerenator
		SignalBase * m_proces;

		// Identification
		Identification * m_identify;
	public:
		RegulatorGPC(void);
		~RegulatorGPC(void);
		double simulate(double input);
		void set_parameters(std::map<std::string, double> & parm);
		void set_parameters(const std::string & param_name, double value);
		void get_parameters(std::map<std::string, double> & parm) const;
		virtual RegulatorGPC * clone () const;
		void set_setpoint(SignalBase * proces);
		double get_error(void);
		void get_error(std::vector<double> & err);
		double get_setpoint(void);
	private:
		bool check_parameters(void);
		void start_identification(void);
};

#endif