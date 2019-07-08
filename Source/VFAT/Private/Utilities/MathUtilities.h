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

#pragma once

#include "CoreMinimal.h"


class MathUtilities
{
public:
    static float DegreeToRad(float Angle);
    
    static float RadToDegree(float Angle);
   
    static void GeographicToCartesian(float Longitude, float Latitude, float Radius, float &X, float &Y, float &Z);
    
    static void CartesianToSpherical(float X, float Y, float Z, float &Azimuth, float &Inclination, float &Radius);
};
