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

#include "Transformations.h"

#include <cmath>

namespace SimCache
{

//-----------------------------------------------------------------------------

VectorR3 Transformations::FromEllipsoidal(double phi, double lambda, double h)
{
    auto N = a / sqrt(1.0 - (eSquared * pow(sin(phi), 2.0)));
    auto x = (N + h) * cos(phi) * cos(lambda);
    auto y = (N + h) * cos(phi) * sin(lambda);
    auto z = ((1.0 - eSquared) * N + h) * sin(phi);
    return VectorR3(x, y, z);
}

//-----------------------------------------------------------------------------

} // namespace SimCache
