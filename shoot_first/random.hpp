#ifndef _RANDOM_HPP_
#define _RANDOM_HPP_

#include <ctime>
#include <cstdlib>

class Random{
public:
	static void genSeed(){ srand(time(NULL)); }
	static unsigned int genUInteger(){ return rand(); }
	static unsigned int genUInteger(unsigned int min, unsigned int max){ if (min == max) return min; return (rand() % (max - min + 1)) + min; }
	static int genInteger(int min, int max){
		if (min == max)
			return min;

		if (max < 0){
			return -genInteger(-min, -max);
		}
		else if (min < 0){
			return max - genInteger(0, min*-1 + max);
		}
		
		return (rand() % (max - min)) + min;
	}
};

#endif