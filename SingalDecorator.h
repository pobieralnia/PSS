#ifndef __DEKORATOR_H__
#define __DEKORATOR_H__

#include "Signal.h"
#include <deque>

class Dekorator : public SignalBase
{
	public:
		Dekorator (SignalBase * p);
		virtual ~Dekorator ();
		virtual double simulate (void) = 0;
		virtual bool active (int inp) = 0;
	protected:
		SignalBase * s_proc;
		std::deque<int> s_simulation_step;
};
 
class SignalRectangle : public Dekorator
{
	public:
		SignalRectangle (SignalBase * p, double amp, int period, double fill, int start, int end);
		SignalRectangle (SignalBase * p, double amp, int period, double fill);
		virtual double simulate (void);
		virtual bool active (int inp);
	private:
		double m_amp;
		int m_period;
		double m_fill;
		int m_start;
		int m_end;
		bool m_continues;
};

class SignalStep : public Dekorator
{
	public:
		SignalStep (SignalBase * p, double w, int start, int end);
		SignalStep (SignalBase * p, double w);
		virtual double simulate (void);
		virtual bool active (int inp);
	private:
		double m_w;
		int m_start;
		int m_end;
		bool m_continues;
};
 
#endif