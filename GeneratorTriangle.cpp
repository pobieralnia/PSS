#include "stdafx.h"
/*
#include "StdAfx.h"
#include "GeneratorTriangle.h"


GeneratorTraingle::GeneratorTraingle(std::map<std::string,int> parameters, int start, int stop)
{
	Signal(start, stop);
	this->m_frequence = parameters['triangle_frequency'];
	this->m_amplitude = parameters['triangle_amplitude']; 
}


double GeneratorTraingle::Simulate(int t)
{
	m_output = 0;

	if(Signal::if_active(t))
	{
		const long triTime = static_cast<int>(1.0/this->frequency)+1;
        const long t = time % triTime;
        const double halfTime = triTime/2.0;

        if (t <= halfTime)
            this->output += (t/halfTime) * this->amplitude;
        else
            this->output += (1 - (t-halfTime)/halfTime) * this->amplitude;

		return this->output;
	}
}
*/