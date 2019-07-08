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


#include "EquidistantField.h"

#include "Utilities/Constants.h"
#include "Utilities/MathUtilities.h"


void UEquidistantField::Init(FEquidistantProgram Program)
{
    this->Program = Program;
    Reset();
}

float UEquidistantField::GetThresholdValue(int32 Index)
{
    return Program.ThresholdsAsArray[Index];
}

/**
 * This method tries to sample Program.Test_Positions points, which are about equidistantly
 * distributed, on a spherical segment (see http://mathworld.wolfram.com/SphericalSegment.html).
 * However, the resulting number of points may not exactly equal Program.Test_Positions
 * because the used algorithm is actually designed to sample a certain number of points on a
 * complete sphere, not only a spherical segment.
 *
 * Notation and definitions from http://mathworld.wolfram.com/SphericalCap.html
 * Algorithm from Gonzalez - Measurement of Areas on a Sphere Using Fibonacci and Latitude–Longitude Lattices
 * which is based on Swinbank and Purser - Fibonacci grids: A novel approach to global modelling
 */
void UEquidistantField::Reset()
{
    UVisualField::Reset();
    
    const float GoldenRatio = (1.0f + FGenericPlatformMath::Sqrt(5.0f)) / 2.0f;
    const float SphereSurface = 4.0f * PI * Constants::MESH_RADIUS * Constants::MESH_RADIUS;

    // Cosinus instead of sinus (http://mathworld.wolfram.com/SphericalCap.html) because z axis of
    // assumed coordinate system is identical to gaze direction (here, 'R-h'-direction in
    // http://mathworld.wolfram.com/SphericalCap.html)
    const float RMinusH = FGenericPlatformMath::Cos(MathUtilities::DegreeToRad(Program.Max_Inclination)) * Constants::MESH_RADIUS;
    const float H = Constants::MESH_RADIUS - RMinusH;
    const float SegmentSurface = 2.0f * PI * Constants::MESH_RADIUS * H;

    // Program.Test_Positions points should be on the spherical segment, P points on the entire sphere,
    // so NumberSamples = P * SurfaceRatio and P = NumberSamples / SurfaceRatio
    // P = 2N + 1 per definition (see Swinbank and Purser), so N = (P - 1) / 2
    const float SurfaceRatio = SegmentSurface / SphereSurface;
    const float P = Program.Test_Positions / SurfaceRatio;
    const int32 N = FGenericPlatformMath::CeilToInt((P - 1.0f) / 2.0f);

    for (int i = -N; i <= N; i++)
    {
        float Latitude = MathUtilities::RadToDegree(FGenericPlatformMath::Asin((2.0f * i) / (2.0f * N + 1.0f)));
        float Longitude = FGenericPlatformMath::Fmod(i, GoldenRatio) * 360.0f / GoldenRatio;

        if (Longitude < -180.0f)
        {
            Longitude = 360.0f + Longitude;
        }
        if (Longitude > 180.0f)
        {
            Longitude = Longitude - 360.0f;
        }

        if (CheckPosition(Longitude, Latitude))
        {
            UEquidistantPosition* Position = NewObject<UEquidistantPosition>(this);
            Position->Init(Program.ThresholdsAsArray.Num(), Longitude, Latitude, Program.Eye);
            Positions.Add(Position);
        }
    }
}

/*
 * Checks if the point is on the spherical segment between Program.Min_Inclination and Program.Max_Inclination
 */
bool UEquidistantField::CheckPosition(float Longitude, float Latitude)
{
    float X, Y, Z;
    MathUtilities::GeographicToCartesian(Longitude, Latitude, Constants::MESH_RADIUS, X, Y, Z);
    
    // Geographic coordinate system has 0, 0 at equator,
    // whereas spherical coordinate system has 0, 0 at north pole
    FVector Position(X, Y, Z);
    Position = Position.RotateAngleAxis(-90.0f, FVector(0, 1, 0));
    
    float Azimuth, Inclination, Radius;
    MathUtilities::CartesianToSpherical(Position.X, Position.Y, Position.Z, Azimuth, Inclination, Radius);
    
    return (Inclination <= Program.Max_Inclination && Inclination >= Program.Min_Inclination);
}

