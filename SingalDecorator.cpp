#include "StdAfx.h"
#include "SingalDecorator.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
 
Dekorator::Dekorator (SignalBase * p)  : s_proc(p) 
{
	s_simulation_step.clear();
	s_simulation_step.push_back(0);
}
     
Dekorator::~Dekorator () 
{
    delete s_proc;
}
 
SignalRectangle::SignalRectangle (SignalBase * p, double amp, int period, double fill)  : Dekorator(p), m_amp(amp), m_period(period), m_fill(fill), m_start(0), m_end(0)
{
	if(m_period <= 0)
	{
		m_period = 1;
	}

	m_continues = true;
}
 
SignalRectangle::SignalRectangle (SignalBase * p, double amp, int period, double fill, int start, int end)  : Dekorator(p), m_amp(amp), m_period(period), m_fill(fill), m_start(start), m_end(end)
{
	m_continues = false;
}

double SignalRectangle::simulate ()
{
	double rectangle = 0.0;
	int inp = s_simulation_step.back();

	if (active(inp))
		rectangle = ((inp % m_period) < (m_fill * m_period)) ? m_amp : 0;

	s_simulation_step.push_back(inp + 1);
	return s_proc->simulate() + rectangle;
}

bool SignalRectangle::active (int inp)
{
	if(!m_continues)
		return (inp >= m_start && inp <= m_end) ? true : false;
	else
		return true;
}

SignalStep::SignalStep (SignalBase * p, double w)  : Dekorator(p), m_w(w), m_start(0), m_end(0)
{
	m_continues = true;
}
 
SignalStep::SignalStep (SignalBase * p, double w, int start, int end)  : Dekorator(p), m_w(w), m_start(start), m_end(end)
{
	m_continues = false;
}

double SignalStep::simulate ()
{
	double step = 0.0;
	int inp = s_simulation_step.back();

	if (active(inp))
		step = m_w;

	s_simulation_step.push_back(inp + 1);
	return s_proc->simulate() + step;
}

bool SignalStep::active (int inp)
{
	if(!m_continues)
		return (inp >= m_start && inp <= m_end) ? true : false;
	else
		return true;
}