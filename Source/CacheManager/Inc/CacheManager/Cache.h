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
#include <string>

#include <CacheManager/Transformations.h>
#include <CacheManager/VectorR3.h>

namespace SimCache
{

//-----------------------------------------------------------------------------

struct CachePosition
{
    double Latitude;
    double Longitude;
    double Altitude;
    double Pitch;
    double Bank;
    double Heading;
};

//-----------------------------------------------------------------------------

class ICache
{
public:
    typedef std::shared_ptr<ICache> Ptr;

    virtual ~ICache() {}

    virtual std::string const& GetName() const = 0;
    virtual std::string const& GetHint() const = 0;
    virtual CachePosition GetPosition() const = 0;
    virtual double GetDistance(VectorR3 position) const = 0;
};

//-----------------------------------------------------------------------------

class Factory
{
public:
    static ICache::Ptr Make(
        std::string const& name,
        double latitude,
        double longitude,
        double altitude
    );

    static ICache::Ptr Make(
        std::string const& name,
        std::string const& hint,
        double latitude,
        double longitude,
        double altitude,
        double alertDistance,
        double acquireDistance
    );
};

//-----------------------------------------------------------------------------

} // namespace SimCache
