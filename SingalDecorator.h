#ifndef __DEKORATOR_H__
#define __DEKORATOR_H__

#include "Signal.h"
#include <deque>

/**
 * @class	Dekorator SignalDecorator.h
 * @brief	Decorator for signal proces
 */
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
 
/**
 * @class	SignalRectangle	SignalDecorator.h
 * @brief	Generating rectangle signal
 */
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

/**
 * @class	SignalStep	SignalDecorator.h
 * @brief	Generating step signal
 */
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

/**
 * @class	SignalTriangle	SignalDecorator.h
 * @brief	Generating triangle signal
 */
class SignalTriangle : public Dekorator
{
	public:
		SignalTriangle (SignalBase * p, double frequency, double amplitude);
		SignalTriangle (SignalBase * p, double frequency, double amplitude, int start, int end);
		virtual double simulate (void);
		virtual bool active (int inp);
	private:
		double m_amplitude;
		double m_frequency;
		int m_start;
		int m_end;
		bool m_continues;
};

/**
 * @class	SignalSinus	SignalDecorator.h
 * @brief	Generating sinus signal
 */
class SignalSinus : public Dekorator
{
	public:
		SignalSinus (SignalBase * p, int period, double amplitude);
		SignalSinus (SignalBase * p, int period, double amplitude, int start, int end);
		virtual double simulate (void);
		virtual bool active (int inp);
	private:
		double m_amplitude;
		int m_period;
		int m_start;
		int m_end;
		bool m_continues;
};
#endif