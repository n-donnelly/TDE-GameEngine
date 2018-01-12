/*
	Based on code in Game Coding Complete 4th Edition written by 
	Mike McShaffry and David 'Rez' Graham

	Original Code written by Takuji Nishimura and Makoto Matsumoto

	This random number generator keeps a track of numbers generated for debugging purposes
	Generator based on the Mersenne Twister pseudorandom number generator
*/
#include "TDERandomGen.h"
#include <climits>
#include <time.h>

namespace TDE
{

	RandomGen::RandomGen(void)
	{
		rSeed = 1;
		rSeed_sp = 0;
		mti=CMATH_N+1;
	}

	//Returns a random number from 0 to n (excluding n)
	unsigned int RandomGen::Random(unsigned int n)
	{
		unsigned long y;
		static unsigned long mag01[2] = {0x0, CMATH_MATRIX_A};
		if(n==0)
			return 0;

		if(mti >= CMATH_N)
		{
			int k;

			if(mti == CMATH_N+1)
				SetRandomSeed(4355);

			for(k = 0; k < CMATH_N - CMATH_M; k++)
			{
				y = (mt[k] &CMATH_UPPER_MASK) | (mt[k+1] & CMATH_LOWER_MASK);
				mt[k] = mt[k + CMATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
			}

			for(; k < CMATH_N-1; k++)
			{
				y = (mt[k] & CMATH_UPPER_MASK) | (mt[k+1]&CMATH_LOWER_MASK);
				mt[k] = mt[k + (CMATH_M-CMATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
			}

			y = (mt[CMATH_N-1] & CMATH_UPPER_MASK) | (mt[0] &CMATH_LOWER_MASK);
			mt[CMATH_N-1] = mt[CMATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];

			mti = 0;
		}

		y = mt[mti++];
		y ^= CMATH_TEMPERING_SHIFT_U(y);
		y ^= CMATH_TEMPERING_SHIFT_S(y) & CMATH_TEMPERING_MASK_B;
		y ^= CMATH_TEMPERING_SHIFT_T(y) & CMATH_TEMPERING_MASK_C;
		y ^= CMATH_TEMPERING_SHIFT_L(y);

		return (y%n);
	}

	float RandomGen::Random()
	{
		float r = (float)Random(INT_MAX);
		float div = (float)INT_MAX;
		return (r/div);
	}

	void RandomGen::SetRandomSeed(unsigned int n)
	{
		mt[0] = n & 0xffffffff;
		for(mti=1; mti <CMATH_N; mti++)
			mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;

		rSeed = n;
	}

	unsigned int RandomGen::GetSeed(void)
	{
		return rSeed;
	}

	void RandomGen::Randomize(void)
	{
		SetRandomSeed((unsigned int)time(NULL));
	}

}