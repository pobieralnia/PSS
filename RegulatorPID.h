// ---------------------------------------------------------------------------------
// Filename:	RegulatorPID.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		Regulator
// ---------------------------------------------------------------------------------

#ifndef __REGULATORPID_H__
#define __REGULATORPID_H__

#include <deque>
#include "Regulator.h"
#include "Signal.h"

/**
 * @class	RegulatorPID	RegulatorPID.h
 * @brief	Class for simulating regulator PID
 * @date	2012-04-24
 *
 * It inherits from Regulator
 *
 * Exceptions:
 * @see		check_parameters(void)
 * @see		set_parameters(std::map<std::string, double> & parm)
 * @see		set_parameters(const std::string & param_name, double value)
 */
class RegulatorPID : public Regulator
{
	private:
		double m_Tp;
		double m_b;
		double m_k;
		double m_Ti;
		double m_e;
		double m_N;
		double m_Td;
		double m_w;
		std::deque<double> m_history_U, m_history_Y, m_history_Integral, m_history_Proportional, m_history_Differential;
		SignalBase * m_proces;
		std::map<std::string, double> m_tmp_parameter;

	public:
		RegulatorPID(void);
		~RegulatorPID(void);
		double simulate(double input);
		double get_error(void);
		void get_error(std::vector<double> & err);
		void set_parameters(std::map<std::string, double> & parm);
		void set_parameters(const std::string & param_name, double value);
		void get_parameters(std::map<std::string, double> & parm) const;
		virtual RegulatorPID * clone () const;
		void set_setpoint(SignalBase * proces);
		double get_setpoint();

	private:
		double proportional(double w, double y);
		double integral(double e);
		double differential(double y, double previous_y);
		bool check_parameters(void);
};

#endif
