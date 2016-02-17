#pragma once

#define PI    3.14159265

// Integer min() and max() operators
#define imin(i, j) ( (i) < (j) ? (i) : (j) )
#define imax(i, j) ( (i) < (j) ? (j) : (i) )
#define iabs(i) ( i < 0 ? -(i) : (i) )

#ifdef NDEBUG
  #define VEC vec3
  #define MAT mat33
#else
  #define VEC vec
  #define MAT mat
#endif