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

#include <cmath>

#define M_PI 3.14159265358979323846
#define RADIUS_EARTH_M 6366710.0

namespace Conversions
{
    inline double RadiansToDegrees(double radians)
    {
        return radians * 180.0 / M_PI;
    }

    inline double DegreesToRadians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    inline double MetersToFeet(double meters)
    {
        return meters / 0.3048;
    }

    inline double FeetToMeters(double feet)
    {
        return feet * 0.3048;
    }

    inline double MetersToNauticalMiles(double meters)
    {
        return meters / 1852.0;
    }

    inline double NauticalMilesToMeters(double nauticalMiles)
    {
        return nauticalMiles * 1852.0;
    }

    inline double KnotsToMetersPerSecond(double knots)
    {
        return knots * 463.0 / 900.0;
    }

    inline double MetersPerSecondToKnots(double metersPerSecond)
    {
        return metersPerSecond * 900.0 / 463.0;
    }

    inline double DistanceCosines(double lat1, double lon1, double lat2, double lon2)
    {
        return acos((sin(lat1) * sin(lat2)) + (cos(lat1) * cos(lat2) * cos(lon2 - lon1))) * RADIUS_EARTH_M;
    }
};