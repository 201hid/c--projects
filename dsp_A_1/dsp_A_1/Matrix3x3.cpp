
// COS30008, tutorial 3, 2024

#define _USE_MATH_DEFINES     // must be defined before any #include

#include "Matrix3x3.h"

#include <cassert>
#include <cmath>

Matrix3x3::Matrix3x3() noexcept
{
    fRows[0] = Vector3D( 1.0f, 0.0f, 0.0f );
    fRows[1] = Vector3D( 0.0f, 1.0f, 0.0f );
    fRows[2] = Vector3D( 0.0f, 0.0f, 1.0f );
}

Matrix3x3::Matrix3x3( const Vector3D& aRow1, const Vector3D& aRow2, const Vector3D& aRow3 ) noexcept
{
    fRows[0] = aRow1;
    fRows[1] = aRow2;
    fRows[2] = aRow3;
}

const Vector3D Matrix3x3::row( size_t aRowIndex ) const
{
    assert( aRowIndex < 3 );
    
    return fRows[aRowIndex];
}

const Vector3D Matrix3x3::column( size_t aColumnIndex ) const
{
    assert( aColumnIndex < 3 );
    
    return Vector3D( row( 0 )[aColumnIndex],
                     row( 1 )[aColumnIndex],
                     row( 2 )[aColumnIndex] );
}

Matrix3x3 Matrix3x3::operator*( const float aScalar ) const noexcept
{
    return Matrix3x3( row( 0 ) * aScalar,
                      row( 1 ) * aScalar,
                      row( 2 ) * aScalar );
}

Matrix3x3 Matrix3x3::operator+( const Matrix3x3& aOther  ) const noexcept
{
    return Matrix3x3( row( 0 ) + aOther.row( 0 ),
                      row( 1 ) + aOther.row( 1 ),
                      row( 2 ) + aOther.row( 2 ) );
}

Vector3D Matrix3x3::operator*( const Vector3D& aVector ) const noexcept
{
    return Vector3D( row( 0 ).dot( aVector ),
                     row( 1 ).dot( aVector ),
                     row( 2 ).dot( aVector ) );
}

Matrix3x3 Matrix3x3::scale( const float aX, const float aY )
{
    return Matrix3x3( Vector3D( aX, 0.0f, 0.0f ),
                      Vector3D( 0.0f, aY, 0.0f ),
                      Vector3D( 0.0f, 0.0f, 1.0f )
                    );
}

Matrix3x3 Matrix3x3::translate( const float aX, const float aY )
{
    return Matrix3x3( Vector3D( 1.0f, 0.0f, aX ),
                      Vector3D( 0.0f, 1.0f, aY ),
                      Vector3D( 0.0f, 0.0f, 1.0f )
                    );
}

Matrix3x3 Matrix3x3::rotate( const float aAngleInDegree )
{
    float lRadTheta = aAngleInDegree * static_cast<float>(M_PI) / 180.0f;

    float lSinTheta = std::sin( lRadTheta );
    float lCosTheta = std::cos( lRadTheta );
    
    return Matrix3x3( Vector3D( lCosTheta, -lSinTheta, 0.0f ),
                      Vector3D( lSinTheta, lCosTheta, 0.0f ),
                      Vector3D( 0.0f, 0.0f, 1.0f ) );
}

// problem set 1 extensions

Matrix3x3 Matrix3x3:: operator*( const Matrix3x3& aOther ) const noexcept
{
    return Matrix3x3(
        Vector3D(
            this->row(0).dot(aOther.column(0)),  // Top left element
            this->row(0).dot(aOther.column(1)),  // Top middle element
            this->row(0).dot(aOther.column(2))   // Top right element
        ),
        Vector3D(
            this->row(1).dot(aOther.column(0)),  // Middle left element
            this->row(1).dot(aOther.column(1)),  // Center element
            this->row(1).dot(aOther.column(2))   // Middle right element
        ),
        Vector3D(
            this->row(2).dot(aOther.column(0)),  // Bottom left element
            this->row(2).dot(aOther.column(1)),  // Bottom middle element
            this->row(2).dot(aOther.column(2))   // Bottom right element
        )
    );

}




std::ostream& operator<<( std::ostream& aOStream, const Matrix3x3& aMatrix )
{
    return aOStream << "[" << aMatrix.fRows[0].toString()<< "," << aMatrix.fRows[1].toString() << "," << aMatrix.fRows[2].toString() << "]" ;
}

float Matrix3x3:: det() const noexcept
{
    float a1 = row(0).x();//1
    float b1 = row(0).y();//2
    float c1 = row(0).w();//3
    float a2 = row(1).x();//4
    float b2= row(1).y();//5
    float c2 = row(1).w();//6
    float a3 = row(2).x();//7
    float b3 = row(2).y();//8
    float c3 = row(2).w();//9

    float det = a1*((b2*c3) - (c2*b3)) - b1*((a2*c3)-(a3*c2)) + c1*((a2*b3 )-(a3*b2));
    
    return det;
}

Matrix3x3 Matrix3x3 :: transpose() const noexcept
{
    return Matrix3x3(Vector3D(row(0).x(),row(1).x(), row(2).x() ),
                     Vector3D(row(0).y(),row(1).y(),row(2).y() ),
                     Vector3D(row(0).w(),row(1).w(), row(2).w() ));
}

bool Matrix3x3 ::hasInverse() const noexcept
{
    if (det() == 0)
        return false;
    else
        return true;
}

Matrix3x3 Matrix3x3 :: inverse() const noexcept
{
    float det = this->det();

    float a1 = row(0).x();//1
    float b1 = row(0).y();//2
    float c1 = row(0).w();//3
    float a2 = row(1).x();//4
    float b2= row(1).y();//5
    float c2 = row(1).w();//6
    float a3 = row(2).x();//7
    float b3 = row(2).y();//8
    float c3 = row(2).w();//9
    
    Matrix3x3 inverse = Matrix3x3(
                                   Vector3D((b2 * c3 - b3 * c2), -(b1 * c3 - b3 * c1), (b1 * c2 - b2 * c1)),
                                   Vector3D(-(a2 * c3 - a3 * c2), (a1 * c3 - a3 * c1), -(a1 * c2 - a2 * c1)),
                                   Vector3D((a2 * b3 - a3 * b2), -(a1 * b3 - a3 * b1), (a1 * b2 - a2 * b1))
     
                                  );
    
    assert(det != 0);
    return inverse *(1.0f /det );
}
