#include "stdafx.h"
/*

#include "GeneratorStep.h"

GeneratorStep::GeneratorStep(std::map<string,int> parameters, int start, int stop)
{
	Signal(start, stop);
	this->m_frequence = parameters['rectangle_frequence'];
	this->m_amplitude = parameters['rectangle_amplituda']; 
	this->m_fill = parameters['rectangle_fill'];
}


double GeneratorStep::Simulate(int t)
{
	this->m_output = 0;

	if(Signal::if_active(t))
	{
        const long rectTime = static_cast<int>(1.0/this->m_frequency)+1;
        const long t = time % rectTime;
        if (t < rectTime*this->m_fill)
        {
            this->m_output += this->m_amplitude;
        }

		return this->m_output;
	}
}
*/