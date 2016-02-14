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

#include <CacheManager/VectorR3.h>

namespace SimCache
{
namespace Transformations
{

//-----------------------------------------------------------------------------

// WGS84 constants
const double a = 6378137.0; // semi-major axis (a)
const double f = 1.0 / 298.257223563; // flattening (f)
const double b = a * (1.0 - f); // semi-minor axis (b) (6356752.3142 meters)
const double eSquared = 2.0 * f - (f * f); // first eccentricity squared (e^2) (6.69437999014 x 10-3)
const double ePrimeSquared = (a * a) / (b * b) - 1.0; // second eccentricity squared (e'^2) (6.73949674228 x 10-3)

//-----------------------------------------------------------------------------

VectorR3 FromEllipsoidal(double phi, double lambda, double h);

//-----------------------------------------------------------------------------

} // namespace Transformations
} // namespace SimCache
