#include <stdlib.h>
#include "measurments.h"

float Measurments::distance(const Point& p1, const Point& p2)
{
    return sqrt(pow(p2.y - p1.y, 2) + pow(p2.x - p1.x, 2));
}


float Measurments::angleBetween(const Point& p1, const Point& p2)
{
    //Behold a perfect application of arc tangent.
    return atan2(p2.y - p1.y, p2.x - p1.x);
}


bool Measurments::isClose(const Point& p1, const Point& p2, float tol)
{
    return (fabs(p1.y - p2.y) <= tol) && (fabs(p2.x - p1.x) <= tol);
}

float Measurments::angleDiff(float angle1, float angle2){
    // Convert angles to unitary complex numbers z1 and z2
    float r1 = cos(angle1);
    float i1 = sin(angle1);
    float r2 = cos(angle2);
    float i2 = sin(angle2);
    // Conjugate z1
    i1 = -i1;
    // Multiply to get z3
    float r3 = r1*r2 - i1 * i2;
    float i3 = i1*r2 + r1 * i2;
    // Get the argument
    float arg = atan2(i3, r3);

    return arg;
}