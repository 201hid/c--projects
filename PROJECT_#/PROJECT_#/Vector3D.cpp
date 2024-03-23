//
//  Vector3D.cpp
//  PROJECT_#
//
//  Created by TOWHIDUL HASSAN on 12/3/2024.
//
#define _USE_MATH_DEFINES     // must be defined before any #include
#include "Vector3D.h"
#include <cassert>
#include <cmath>
#include <stdio.h>

Vector3D :: Vector3D( float aX , float aY , float aW) noexcept :
    fBaseVector(aX, aY),
    fW(aW)
{}


Vector3D :: Vector3D( const Vector2D& aVector ) noexcept : fBaseVector(aVector) , fW(1.0f)
{}


float Vector3D::operator[]( size_t aIndex ) const
{
    assert( aIndex < 3 );
    return *(reinterpret_cast<const float*>(this) + aIndex);
}//didnt understand whats assert and how the function work

 
Vector3D ::  operator Vector2D() const noexcept
{
    float safefw;
    if (fW<=0) {
        safefw = 1.0f;
    }
    else safefw = fW;
    
    return Vector2D(fBaseVector.x() /safefw , fBaseVector.y() / safefw);
}


std::ostream& operator<<( std::ostream& aOStream, const Vector3D& aVector )
{
    return aOStream << "[" << round( aVector.fBaseVector.x() * 1000.0f ) / 1000.0f << "," << round( aVector.fBaseVector.y() * 1000.0f ) / 1000.0f <<"," << round( aVector.w() * 1000.0f ) / 1000.0f << "]";
}


Vector3D Vector3D::operator*( const float aScalar ) const noexcept
{
    return Vector3D(fBaseVector.x() * aScalar,fBaseVector.y() * aScalar, w()* aScalar );
}

Vector3D operator*( const float aScalar, const Vector3D& aVector ) noexcept
{
    return aVector * aScalar;
}


Vector3D Vector3D::operator+( const Vector3D& aOther ) const noexcept
{
    return Vector3D( this->x() + aOther.x(), this->y() + aOther.y(),  this->w() + aOther.w());
}

float Vector3D:: dot( const Vector3D& aOther ) const noexcept
{
    return  (this->x() * aOther.x()) + ( this->y() * aOther.y()) + ( this->w()* aOther.w());

}

