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

#pragma once

#include <memory>

namespace SimCache
{

//-----------------------------------------------------------------------------

class VectorR3
{
public:
    typedef std::shared_ptr<VectorR3> Ptr;

    double X;
    double Y;
    double Z;

    VectorR3(double x, double y, double z)
        : X(x), Y(y), Z(z) { }

    double Norm();
    double NormSquared();

    VectorR3 CrossProduct(VectorR3 rhs);
    double DotProduct(VectorR3 rhs);

    friend VectorR3 operator +(VectorR3 u, VectorR3 v);
    friend VectorR3 operator -(VectorR3 u, VectorR3 v);
    friend VectorR3 operator *(VectorR3 u, double c);
};

//-----------------------------------------------------------------------------

} // namespace SimCache
