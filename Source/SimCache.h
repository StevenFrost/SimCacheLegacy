#pragma once

#include <memory>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "SimConnect.h"

#include "Transformations.h"
#include "VectorR3.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

class ICache
{
public:
    typedef std::shared_ptr<ICache> Ptr;

    virtual ~ICache() {}

    virtual std::string Name() const = 0;
    virtual std::string Hint() const = 0;
    virtual SIMCONNECT_DATA_INITPOSITION InitPosition() const = 0;
    virtual double Distance(VectorR3 position) const = 0;
};

//-----------------------------------------------------------------------------

class Factory
{
public:
    static ICache::Ptr Make(std::string const& name, double latitude, double longitude, double altitude);
    static ICache::Ptr Make(std::string const& name, std::string const& hint, double latitude, double longitude, double altitude, double alertDistance, double acquireDistance);
};

//-----------------------------------------------------------------------------

} // namespace SimCache
