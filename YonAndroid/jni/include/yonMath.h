#ifndef _YON_CORE_MATH_H_
#define _YON_CORE_MATH_H_

#include "yonTypes.h"
#include <math.h>

namespace yon{
namespace core{

//舍入误差
const s32 ROUNDING_ERROR_S32 = 0;
const f32 ROUNDING_ERROR_f32 = 0.000001f;
const f64 ROUNDING_ERROR_f64 = 0.00000001;

//32位
#ifdef PI
#undef PI
#endif

//PI相关定义
const f32 PI=3.1415926535897932384626433832795f;
const f32 PI2=PI+PI;
const f32 RECIPROCAL_PI	= 1.0f/PI;
const f32 HALF_PI	= PI*0.5f;

//从角度转为弧度
const f32 DEGTORAD = PI / 180.0f;
//从弧度转为角度
const f32 RADTODEG   = 180.0f / PI;

//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& min_(const T& a, const T& b)
{
	return a < b ? a : b;
}

//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& min_(const T& a, const T& b, const T& c)
{
	return a < b ? min_(a, c) : min_(b, c);
}

//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& max_(const T& a, const T& b)
{
	return a < b ? b : a;
}

//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& max_(const T& a, const T& b, const T& c)
{
	return a < b ? max_(b, c) : max_(a, c);
}


inline bool equals(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_f64)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

//! returns if a equals b, taking possible rounding errors into account
inline bool equals(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_f32)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

}//core
}//yon

#endif