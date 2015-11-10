#include "Transformations.h"

#include <cmath>

VectorR3 Transformations::FromEllipsoidal(double phi, double lambda, double h)
{
    auto N = a / sqrt(1.0 - (eSquared * pow(sin(phi), 2.0)));
    auto x = (N + h) * cos(phi) * cos(lambda);
    auto y = (N + h) * cos(phi) * sin(lambda);
    auto z = ((1.0 - eSquared) * N + h) * sin(phi);
    return VectorR3(x, y, z);
}