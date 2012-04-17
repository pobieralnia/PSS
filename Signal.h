// ---------------------------------------------------------------------------------
// Filename:	Signal.h
// Author:		Tomasz L.
// Date:		2012-03-24
// ---------------------------------------------------------------------------------

#ifndef __SIGNAL_H__
#define __SIGNAL_H__

/**
 * @class	Signal Signal.h
 * @brief	Base class
 * @date	2012-04-04
 */
class Signal {

	int s_start;
	int s_stop;

	public:
		Signal(int start, int stop) : s_start(start), s_stop(stop) {};
		virtual double simulate(int t) = 0;

	protected:
		bool if_active(int t)
			 {
				return (t >= this->s_start && t<= this->s_stop) ? true : false;	
			 };
};

#endif