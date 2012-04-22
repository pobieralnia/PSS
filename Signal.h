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

	public:
		Signal() {};
		virtual double simulate(int t) = 0;
		virtual ~Signal() {};
};
#endif