// ---------------------------------------------------------------------------------
// Filename:	Regulator.h
// Author:		Tomasz L.
// Date:		2012-03-24
// Package:		Regulator
// ---------------------------------------------------------------------------------

#ifndef __REGULATOR_H__
#define __REGULATOR_H__

#include "Object.h"


public class Regulator : public Object
{
	double m_deviation;

	public:
		virtual double simulate(double objectOutput) = 0;
		virtual ~Regulator(void);

		double get_setpoint();
		void update(  );

		/**
		 * Get deviation
		 *
		 * @return		double
		 */
		double get_deviation() { return this->m_deviation; };
};

#endif