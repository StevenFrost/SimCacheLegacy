/**********************************************************************************
*                                                                                *
* Copyright (c) 2016 Steven Frost, Orion Lyau. All rights reserved.              *
*                                                                                *
* This source is subject to the MIT License.                                     *
* See http://opensource.org/licenses/MIT                                         *
*                                                                                *
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,    *
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED          *
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.         *
*                                                                                *
**********************************************************************************/

#include "VectorR3.h"

#include <cmath>

namespace SimCache
{

//-----------------------------------------------------------------------------

double VectorR3::Norm()
{
    return sqrt((X * X) + (Y * Y) + (Z * Z));
}

double VectorR3::NormSquared()
{
    return (X * X) + (Y * Y) + (Z * Z);
}

VectorR3 VectorR3::CrossProduct(VectorR3 rhs)
{
    return VectorR3((Y * rhs.Z) - (Z * rhs.Y), -((X * rhs.Z) - (Z * rhs.X)), (X * rhs.Y) - (Y * rhs.X));
}

double VectorR3::DotProduct(VectorR3 rhs)
{
    return (X * rhs.X) + (Y * rhs.Y) + (Z * rhs.Z);
}

VectorR3 operator +(VectorR3 u, VectorR3 v) {
    return VectorR3(u.X + v.X, u.Y + v.Y, u.Z + v.Z);
}

VectorR3 operator -(VectorR3 u, VectorR3 v) {
    return VectorR3(u.X - v.X, u.Y - v.Y, u.Z - v.Z);
}

VectorR3 operator *(VectorR3 u, double c) {
    return VectorR3(u.X * c, u.Y * c, u.Z * c);
}

//-----------------------------------------------------------------------------

} // namespace SimCache
