// ---------------------------------------------------------------------------------
// Filename:	GeneratorDecorator.h
// Author:		Tomasz L.
// Date:		2012-03-24
// ---------------------------------------------------------------------------------

#ifndef __GENERATORDECORATOR_H__
#define __GENERATORDECORATOR_H__

#include "Signal.h"

/**
 * @class	GeneratorDecorator GeneratorDecorator.h
 * @brief	Decorator class
 * @date	2012-04-04
 */
class GeneratorDecorator
{
	public:
		GeneratorDecorator(Signal * s) : s_dekorowany(s) {};
		virtual ~GeneratorDecorator() { delete s_dekorowany; };
		virtual double simulate (int t) = 0;
	protected:
		Signal * s_dekorowany;
};

class DekoratorPure : public GeneratorDecorator
{
	public:
		DekoratorPure (Signal * s);
		virtual double simulate (int t);
};

class DekoratorStartu : public GeneratorDecorator
{
	public:
		DekoratorStartu (Signal * s, int start);
		virtual double simulate (int t);
	private:
		int s_start;
};
 
class DekoratorKonca : public GeneratorDecorator
{
	public:
		DekoratorKonca (Signal * s, int koniec);
		virtual double simulate (int t);
	private:
		int s_koniec;
};

#endif