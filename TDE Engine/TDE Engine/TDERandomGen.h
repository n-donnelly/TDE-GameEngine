/*
	Based on code in Game Coding Complete 4th Edition written by 
	Mike McShaffry and David 'Rez' Graham

	Original Code written by Takuji Nishimura and Makoto Matsumoto

	This random number generator keeps a track of numbers generated for debugging purposes
	Generator based on the Mersenne Twister pseudorandom number generator
*/

#ifndef TDE_RANDOM_GEN
#define TDE_RANDOM_GEN

#include <cmath>

#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */   
#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)

namespace TDE
{
	class RandomGen
	{
	private:
		unsigned int	rSeed;
		unsigned int	rSeed_sp;
		unsigned long	mt[CMATH_N];
		int				mti;

	public:
		RandomGen(void);

		unsigned int Random(unsigned int n);
		float Random();
		void SetRandomSeed(unsigned int n);
		unsigned int GetSeed(void);
		void Randomize(void);

	};
}
#endif