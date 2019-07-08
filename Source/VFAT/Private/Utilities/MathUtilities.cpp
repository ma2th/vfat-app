// Copyright 2019 Matthias Ring
// Machine Learning and Data Analytics Lab
// Friedrich-Alexander-University Erlangen-Nuremberg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "MathUtilities.h"


float MathUtilities::DegreeToRad(float Angle)
{
    return (Angle * PI) / 180.0f;
}

float MathUtilities::RadToDegree(float Angle)
{
    return (Angle * 180.0f) / PI;
}

void MathUtilities::GeographicToCartesian(float Longitude, float Latitude, float Radius, float &X, float &Y, float &Z)
{
    float LongitudeInRad = MathUtilities::DegreeToRad(Longitude);
    float LatitudeInRad = MathUtilities::DegreeToRad(Latitude);
    
    X = Radius * FGenericPlatformMath::Cos(LatitudeInRad) * FGenericPlatformMath::Cos(LongitudeInRad);
    Y = Radius * FGenericPlatformMath::Cos(LatitudeInRad) * FGenericPlatformMath::Sin(LongitudeInRad);
    Z = Radius * FGenericPlatformMath::Sin(LatitudeInRad);
}

void MathUtilities::CartesianToSpherical(float X, float Y, float Z, float &Azimuth, float &Inclination, float &Radius)
{
    Radius = FGenericPlatformMath::Sqrt(X * X + Y * Y + Z * Z);
    Inclination = MathUtilities::RadToDegree(FGenericPlatformMath::Acos(Z / Radius));
    Azimuth = MathUtilities::RadToDegree(FGenericPlatformMath::Atan2(Y, Z));
}


