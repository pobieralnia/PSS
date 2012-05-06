// ---------------------------------------------------------------------------------
// Filename:	Signal.h
// Author:		Tomasz L.
// Date:		2012-04-24
// Package:		Signal
// ---------------------------------------------------------------------------------

#ifndef __SIGNAL_H__
#define __SIGNAL_H__

/**
 * @class	SignalBase	Signal.h
 * @brief	Abstract class for Signal generator
 * @date	2012-05-03
 */
class SignalBase
{
	public:
		virtual double simulate (void) = 0;
};

/**
 * @class	Signal	Signal.h
 * @brief	Class to generating signals
 * @date	2012-05-03
 *
 * It inherits class SignalBase, all methods are virtual
 */
class Signal : public SignalBase
{
	public:
		Signal (void) {};
		virtual ~Signal (void) {};
		virtual bool active (int inp) { return true; };
		virtual double simulate (void) { return 0.0; };
};

#endif