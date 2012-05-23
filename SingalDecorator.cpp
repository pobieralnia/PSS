#include "StdAfx.h"
#include "SingalDecorator.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

/**
 * Constructor
 * 
 * @param		SignalBase * p
 * @return		void
 */
Dekorator::Dekorator (SignalBase * p)  : s_proc(p) 
{
	s_simulation_step.clear();
	s_simulation_step.push_back(0);
}
     
/**
 * Destructor
 *
 * @return		void
 */
Dekorator::~Dekorator () 
{
    delete s_proc;
}
 
/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double amp
 * @param		int period
 * @param		double fill
 * @return		void
 */
SignalRectangle::SignalRectangle (SignalBase * p, double amp, int period, double fill)  : Dekorator(p), m_amp(amp), m_period(period), m_fill(fill), m_start(0), m_end(0)
{
	if(m_period <= 0)
	{
		m_period = 1;
	}

	m_continues = true;
}

/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double amp
 * @param		int period
 * @param		double fill
 * @param		int start
 * @param		int end
 * @return		void
 */
SignalRectangle::SignalRectangle (SignalBase * p, double amp, int period, double fill, int start, int end)  : Dekorator(p), m_amp(amp), m_period(period), m_fill(fill), m_start(start), m_end(end)
{
	m_continues = false;
}

/**
 * Generate one sample
 *
 * @return		double
 */
double SignalRectangle::simulate ()
{
	double rectangle = 0.0;
	int inp = s_simulation_step.back();

	if (active(inp))
		rectangle = ((inp % m_period) < (m_fill * m_period)) ? m_amp : 0;

	s_simulation_step.push_back(inp + 1);
	return s_proc->simulate() + rectangle;
}

/**
 * Check if signal is still active
 *
 * @param		int inp
 * @return		bool
 */
bool SignalRectangle::active (int inp)
{
	if(!m_continues)
		return (inp >= m_start && inp <= m_end) ? true : false;
	else
		return true;
}

/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double w
 * @return		void
 */
SignalStep::SignalStep (SignalBase * p, double w)  : Dekorator(p), m_w(w), m_start(0), m_end(0)
{
	m_continues = true;
}
 
/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double w
 * @param		int start
 * @param		int end
 * @return		void
 */
SignalStep::SignalStep (SignalBase * p, double w, int start, int end)  : Dekorator(p), m_w(w), m_start(start), m_end(end)
{
	m_continues = false;
}

/**
 * Generate one sample
 *
 * @return		double
 */
double SignalStep::simulate ()
{
	double step = 0.0;
	int inp = s_simulation_step.back();

	if (active(inp))
		step = m_w;

	s_simulation_step.push_back(inp + 1);
	return s_proc->simulate() + step;
}

/**
 * Check if signal is still active
 *
 * @param		int inp
 * @return		bool
 */
bool SignalStep::active (int inp)
{
	if(!m_continues)
		return (inp >= m_start && inp <= m_end) ? true : false;
	else
		return true;
}

// --------------------------------------------------------------------------------------------------------------------------

/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double frequency
 * @param		double amplitude
 * @return		void
 */
SignalTriangle::SignalTriangle (SignalBase * p, double frequency, double amplitude)  : Dekorator(p), m_frequency(frequency), m_amplitude(amplitude), m_start(0), m_end(0)
{
	m_continues = true;
}
 
/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double frequency
 * @param		double amplitude
 * @param		int start
 * @param		int end
 * @return		void
 */
SignalTriangle::SignalTriangle (SignalBase * p, double frequency, double amplitude, int start, int end)  : Dekorator(p), m_frequency(frequency), m_amplitude(amplitude), m_start(start), m_end(end)
{
	m_continues = false;
}

/**
 * Generate one sample
 *
 * @return		double
 */
double SignalTriangle::simulate ()
{
	double triangle = 0.0;
	int inp = s_simulation_step.back();

	if (active(inp))
	{
		const long triTime = static_cast<int>(1.0/m_frequency)+1;
        const double halfTime = triTime/2.0;

        if (inp <= halfTime)
            triangle = (inp/halfTime) * m_amplitude;
        else
            triangle = (1 - (inp-halfTime)/halfTime) * m_amplitude;
	}

	s_simulation_step.push_back(inp + 1);
	return s_proc->simulate() + triangle;
}

/**
 * Check if signal is still active
 *
 * @param		int inp
 * @return		bool
 */
bool SignalTriangle::active (int inp)
{
	if(!m_continues)
		return (inp >= m_start && inp <= m_end) ? true : false;
	else
		return true;
}

// --------------------------------------------------------------------------------------------------------------------------

/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double period
 * @param		double amplitude
 * @return		void
 */
SignalSinus::SignalSinus (SignalBase * p, int period, double amplitude)  : Dekorator(p), m_period(period), m_amplitude(amplitude), m_start(0), m_end(0)
{
	m_continues = true;
}

/**
 * Constructor
 *
 * @param		SignalBase * p - pointer to previous signal
 * @param		double period
 * @param		double amplitude
 * @param		int start
 * @param		int end
 * @return		void
 */
SignalSinus::SignalSinus (SignalBase * p, int period, double amplitude, int start, int end)  : Dekorator(p), m_period(period), m_amplitude(amplitude), m_start(start), m_end(end)
{
	m_continues = false;
}

/**
 * Generate one sample
 *
 * @return		double
 */
double SignalSinus::simulate ()
{
	double sinus = 0.0;
	int inp = s_simulation_step.back();

	if (active(inp))
	{
		sinus = m_amplitude*std::sin((static_cast<double>(inp % m_period) / m_period) * 6.28);
	}

	s_simulation_step.push_back(inp + 1);
	return s_proc->simulate() + sinus;
}

/**
 * Check if signal is still active
 *
 * @param		int inp
 * @return		bool
 */
bool SignalSinus::active (int inp)
{
	if(!m_continues)
		return (inp >= m_start && inp <= m_end) ? true : false;
	else
		return true;
}