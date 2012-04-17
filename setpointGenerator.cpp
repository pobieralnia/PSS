#include "StdAfx.h"
#include "setpointGenerator.h"

#include <string>
#include <map>
#include <cmath>


setpointGenerator::setpointGenerator(void)
{
	this->m_enable_sinus(false);
	this->m_enable_step(false);
	this->m_time(0);
}

double setpointGenerator::get_value() const
{
    double output = 0;

    if (this->m_enable_sinus)
    {
        output += sinus.amplitude * sin(this->m_time*sinus.frequency);
    }
	if (this->m_enable_triangle)
    {
        const long triTime = static_cast<int>(1.0/triangle.frequency)+1;
        const long t = time % triTime;
        const double halfTime = triTime/2.0;

        if (t <= halfTime)
            output += (t/halfTime) * triangle.amplitude;
        else
            output += (1 - (t-halfTime)/halfTime) * triangle.amplitude;
    }
	if (this->m_enable_rectangle)
    {
        const long rectTime = static_cast<int>(1.0/rectangle.frequency)+1;
        const long t = time % rectTime;
        if (t < rectTime*rectangle.fill)
        {
            output += rectangle.amplitude;
        }
    }
    if (this->m_enable_step)
    {
        if (this->m_time >= step.time)
        {
            output += step.value;
        }
    }

    return output;
}

void setpointGenerator::update()
{
    this->m_time++;
}

void setpointGenerator::set_parameters(std::map<std::string, int> params)
{
	
}