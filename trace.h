#ifndef TRACER_H
#define TRACER_H

#include <sys/types.h>
#include <sys/time.h>

class Tracer
{
public:

	typedef unsigned long res_t;
	timeval begin;

	Tracer()
	{
		gettimeofday(&begin, NULL);
	}

	void restart()
	{
		gettimeofday(&begin, NULL);
	}

	res_t operator() ()
	{
		timeval e;
		gettimeofday(&e, NULL);
		return (e.tv_usec - begin.tv_usec) + (e.tv_sec - begin.tv_sec) * 1000000;
	}
	
};

#endif // TRACER_H
