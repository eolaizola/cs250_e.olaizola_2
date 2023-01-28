#ifndef MATHUTILITIES_H
#define MATHUTILITIES_H

#include <limits>

// Do not change
static const float EPSILON = std::numeric_limits<float>::epsilon();

// Macro definitions
#define isZero(x) ((x < EPSILON) && (x > -EPSILON))
#define isEqual(x,y) (((x >= y) ? (x-y) : (y-x)) < EPSILON)

#endif