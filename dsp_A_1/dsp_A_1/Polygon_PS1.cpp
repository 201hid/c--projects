
// COS30008, Tutorial 2, 2023

#include "Polygon.h"

#include <cassert>



float Polygon ::getSignedArea() const noexcept
{
    float area = 0.0f;
    for (int i = 0; i < fNumberOfVertices; i++) {
        int nextvertice = (i + 1) % fNumberOfVertices; // For xi+1 and yi+1, with wrap-around
        area += (fVertices[i].y() + fVertices[nextvertice].y()) * (fVertices[i].x() - fVertices[nextvertice].x());
    }
    return area / 2.0f; // The formula divides the total by 2
}

Polygon Polygon :: transform( const Matrix3x3& aMatrix ) const noexcept
{
    Vector3D vector3D;
    Polygon Result = *this;
    
    for (int i = 0; i < fNumberOfVertices  ; i++)
        
    {
        vector3D = aMatrix * Vector3D(fVertices[i]);
        Vector2D vector2d = Vector2D(vector3D.x(),vector3D.y() );
        Result.fVertices[i] = vector2d;

    }
    
    return Result;
    
    
}
