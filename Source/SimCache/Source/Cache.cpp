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

#include "Conversions.h"
#include "Cache.h"

namespace SimCache
{

//-----------------------------------------------------------------------------

class CacheImpl : public ICache
{
public:
    CacheImpl(std::string const& name, double latitude, double longitude, double altitude);
    CacheImpl(std::string const& name, std::string const& hint, double latitude, double longitude, double altitude, double alertDistance, double acquireDistance);
    ~CacheImpl() {};

    virtual std::string const& Name() const;
    virtual std::string const& Hint() const;
    virtual SIMCONNECT_DATA_INITPOSITION InitPosition() const;
    virtual double Distance(VectorR3 position) const;

private:
    std::string m_name;
    std::string m_hint;

    double m_latitudeDegrees;
    double m_longitudeDegrees;
    double m_altitudeFeet;
    double m_pitchDegrees;
    double m_bankDegrees;
    double m_headingDegrees;

    VectorR3 m_positionCartesian;

    double m_alertDistanceMeters;
    double m_acquireDistanceMeters;
};

//-----------------------------------------------------------------------------

CacheImpl::CacheImpl(std::string const& name, double latitude, double longitude, double altitude)
    :
    m_name(name),
    m_hint("No hint given."),
    m_latitudeDegrees(latitude),
    m_longitudeDegrees(longitude),
    m_altitudeFeet(altitude),
    m_pitchDegrees(0.0),
    m_bankDegrees(0.0),
    m_headingDegrees(0.0),
    m_positionCartesian(Transformations::FromEllipsoidal(Conversions::DegreesToRadians(latitude), Conversions::DegreesToRadians(longitude), Conversions::FeetToMeters(altitude))),
    m_alertDistanceMeters(1000.0),
    m_acquireDistanceMeters(50.0)
{}

CacheImpl::CacheImpl(std::string const& name, std::string const& hint, double latitude, double longitude, double altitude, double alertDistance, double acquireDistance)
    :
    m_name(name),
    m_hint(hint),
    m_latitudeDegrees(latitude),
    m_longitudeDegrees(longitude),
    m_altitudeFeet(altitude),
    m_pitchDegrees(0.0),
    m_bankDegrees(0.0),
    m_headingDegrees(0.0),
    m_positionCartesian(Transformations::FromEllipsoidal(Conversions::DegreesToRadians(latitude), Conversions::DegreesToRadians(longitude), Conversions::FeetToMeters(altitude))),
    m_alertDistanceMeters(alertDistance),
    m_acquireDistanceMeters(acquireDistance)
{}

std::string const& CacheImpl::Name() const
{
    return m_name;
}

std::string const& CacheImpl::Hint() const
{
    return m_hint;
}

SIMCONNECT_DATA_INITPOSITION CacheImpl::InitPosition() const
{
    SIMCONNECT_DATA_INITPOSITION InitPos;
    InitPos.Latitude = m_latitudeDegrees;
    InitPos.Longitude = m_longitudeDegrees;
    InitPos.Altitude = m_altitudeFeet;
    InitPos.Pitch = m_pitchDegrees;
    InitPos.Bank = m_bankDegrees;
    InitPos.Heading = m_headingDegrees;
    InitPos.OnGround = 0;
    InitPos.Airspeed = 0;
    return InitPos;
}

double CacheImpl::Distance(VectorR3 position) const
{
    return (m_positionCartesian - position).Norm();
}

//-----------------------------------------------------------------------------

ICache::Ptr Factory::Make(std::string const& name, double latitude, double longitude, double altitude)
{
    return std::make_shared<CacheImpl>(name, "No hint given.", latitude, longitude, altitude, 1000.0, 50.0);
}

ICache::Ptr Factory::Make(std::string const& name, std::string const& hint, double latitude, double longitude, double altitude, double alertDistance, double acquireDistance)
{
    return std::make_shared<CacheImpl>(name, hint, latitude, longitude, altitude, alertDistance, acquireDistance);
}

//-----------------------------------------------------------------------------

} // namespace SimCache