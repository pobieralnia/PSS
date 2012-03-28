// ---------------------------------------------------------------------------------
// Filename:	Object.h
// Author:		Tomasz L.
// Date:		2012-03-24
// ---------------------------------------------------------------------------------

#ifndef __OBJECT_H__
#define __OBJECT_H__

/**
 * @class		Object Object.h
 * @brief		Abstract class
 * @author:		Tomasz L
 * @date:		2012-03-20
 */
class Object {
	public:
		virtual double simulate (double input) = 0;
		virtual ~Object() {};
};

#endif