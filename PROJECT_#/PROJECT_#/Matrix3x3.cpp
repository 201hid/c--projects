//
//  Matrix3x3.cpp
//  PROJECT_#
//
//  Created by TOWHIDUL HASSAN on 19/3/2024.
//

#define _USE_MATH_DEFINES     // must be defined before any #include
#include "Matrix3x3.h"
#include <cassert>
#include <cmath>
#include <stdio.h>

Matrix3x3 :: Matrix3x3( const Vector3D& aRow1  , const Vector3D& aRow2, const Vector3D& aRow3 ) noexcept 
{
    fRows[0] = aRow1  ;
    fRows[1] = aRow2;
    fRows[2] = aRow3;
}

Matrix3x3 :: Matrix3x3() noexcept
{
    fRows[0] = Vector3D(1.0f, 0.0f, 0.0f);
    fRows[1] = Vector3D(0.0f, 1.0f, 0.0f);
    fRows[2] = Vector3D(0.0f, 0.0f, 1.0f);

}


Matrix3x3  Matrix3x3 :: operator*( const float aScalar ) const noexcept
{
    return Matrix3x3( fRows[0] * aScalar, fRows[1] * aScalar, fRows[2] * aScalar);
}

Matrix3x3 Matrix3x3 :: operator+( const Matrix3x3& aOther ) const noexcept
{
    return Matrix3x3( fRows[0] + aOther.fRows[0], fRows[1] + aOther.fRows[1], fRows[2] + aOther.fRows[2] );
    
}


Vector3D Matrix3x3 ::  operator*( const Vector3D& aVector ) const noexcept

{
    return Vector3D(fRows[0].x() * aVector.x() +fRows[0].y() * aVector.y() + fRows[0].w() * aVector.w(), fRows[1].x() * aVector.x() +fRows[1].y() * aVector.y() + fRows[1].w() * aVector.w(), fRows[2].x() * aVector.x() +fRows[2].y() * aVector.y() + fRows[2].w() * aVector.w() );
}

Matrix3x3 Matrix3x3 :: scale( const float aX , const float aY  )
{
    
    return Matrix3x3(
                     Vector3D(aX, 0.0f, 0.0f),
                     Vector3D(0.0f, aY, 0.0f),
                     Vector3D(0.0f, 0.0f, 1));
}

Matrix3x3 Matrix3x3 :: translate( const float aX , const float aY  )
{
    
    return Matrix3x3(
                     Vector3D(0.0f, 0.0f, aX),
                     Vector3D(0.0f, 1.0f, aY),
                     Vector3D(0.0f, 0.0f, 1));
}



Matrix3x3 Matrix3x3 :: rotate( const float aAngleInDegree )
{
    float lRadTheta = aAngleInDegree * static_cast<float>(M_PI/ 180.0f);
    float lSinTheta = std:: sin(lRadTheta);
    float lCosTheta = std:: cos(lRadTheta);

    return Matrix3x3(
                     Vector3D(lCosTheta, - lSinTheta, 0),
                     Vector3D(lSinTheta, lCosTheta, 0),
                     Vector3D(0.0f, 0.0f, 1));
}


const Vector3D Matrix3x3 ::  row( size_t aRowIndex ) const
{
    assert ( aRowIndex < 3);
    return fRows[aRowIndex];
}


const Vector3D Matrix3x3 ::  column( size_t aColumnIndex ) const
{
    assert ( aColumnIndex < 3);
    return Vector3D(fRows[0][aColumnIndex], fRows[1][aColumnIndex], fRows[2][aColumnIndex]);
}
