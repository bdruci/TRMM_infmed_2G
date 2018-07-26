#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include <vector>
#include <stdlib.h>
#include <cmath>


double fRand(double fMin, double fMax);
//PURPOSE: generate a random double between fMin and fMax
//INPUT: fMin: the minumum value you wish to set the range of random numbers to
//       fmax: the maximum ''
//RETURNS: a random number between these two value
//MODIFIES: N/A


std::vector<double> vecSum(std::vector<double> v1, std::vector<double> v2);
//PURPOSE: adds the vectors element by element
//INPUT: the two equally sized vectors, v1 and v2
//RETURNS: their sum
//MODIFIES: N/A
//REQUIRES: The vectors must be the same length


#endif
