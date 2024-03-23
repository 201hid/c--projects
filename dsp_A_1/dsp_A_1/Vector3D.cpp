
// COS30008, tutorial 3, 2024

#include "Vector3D.h"
#include <iomanip> // Include for std::setprecision
#include <sstream>
#include <cassert>
#include <cmath>

Vector3D::Vector3D( float aX, float aY, float aW ) noexcept :
    fBaseVector(aX, aY),
    fW(aW)
{}

Vector3D::Vector3D( const Vector2D& aVector ) noexcept :
    fBaseVector(aVector),
    fW(1.0f)
{}

float Vector3D::operator[]( size_t aIndex ) const
{
    assert( aIndex < 3 );

    return *(reinterpret_cast<const float*>(this) + aIndex);
}

Vector3D::operator Vector2D() const noexcept
{
     return Vector2D( fBaseVector.x()/fW, fBaseVector.y()/fW );
}
           
Vector3D Vector3D::operator*( const float aScalar ) const noexcept
{
    return Vector3D( x() * aScalar, y() * aScalar, w() * aScalar );
}

Vector3D Vector3D::operator+( const Vector3D& aOther ) const noexcept
{
    return Vector3D( x() + aOther.x(), y() + aOther.y(), w() + aOther.w() );
}

float Vector3D::dot( const Vector3D& aOther ) const noexcept
{
    return x() * aOther.x() + y() * aOther.y() + w() * aOther.w();
}

std::ostream& operator<<( std::ostream& aOStream, const Vector3D& aVector )
{
    return aOStream << static_cast<Vector2D>(aVector);
}



std::string Vector3D::toString() const noexcept {
    std::ostringstream stream;
    stream << "[";

    // A lambda function to format a single component based on its value
    auto formatcordinate = [&stream](float cordinate) {
        if (std::floor(cordinate) == cordinate) {
            // cordinate is an integer, output without decimal point
            stream << static_cast<int>(cordinate);
        } else {
            // cordinate is not an integer
            if (std::abs(cordinate) < 10000) {
                // For non-integer values less than 10000, show up to 4 decimal places
                stream << std::fixed << std::setprecision(4) << cordinate;
            } else {
                // For values 10000 or above, show only 1 decimal place
                stream << std::fixed << std::setprecision(1) << cordinate;
            }
        }
    };

    // Format and append each component of the vector to the stream
    formatcordinate(x());
    stream << ",";
    formatcordinate(y());
    stream << ",";
    formatcordinate(w());

    stream << "]";

    return stream.str();
}

