#pragma once

#include <memory>
#include <string>

#include "Transformations.h"
#include "VectorR3.h"

class SimCache
{
public:
    typedef std::shared_ptr<SimCache> Ptr;

    SimCache(std::string const& name, double latitude, double longitude, double altitude, double acquireDistance)
        :
        m_name(name),
        m_positionCartesian(Transformations::FromEllipsoidal(latitude, longitude, altitude)),
        m_acquireDistanceMeters(acquireDistance)
    { }

    std::string GetName() { return m_name; }
    double GetDistance(VectorR3 position) { return (m_positionCartesian - position).Norm(); }

private:
    std::string m_name;
    VectorR3 m_positionCartesian;
    double m_acquireDistanceMeters;
};