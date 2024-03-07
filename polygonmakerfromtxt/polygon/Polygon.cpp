//
//  Polygon.cpp
//  lab2
//
//  Created by TOWHIDUL HASSAN on 5/3/2024.
//

#include <stdio.h>
#include "Polygon.h"

Polygon :: Polygon() noexcept : fNumberOfVertices(0)
{
    
}

size_t Polygon ::  getNumberOfVertices() const noexcept
{
    return fNumberOfVertices;
}

void Polygon ::  readData( std::istream& aIStream )
{
    Vector2D vector;
    size_t count = 0;
    
    while( count<MAX_VERTICES && aIStream >> vector)
    {
        fVertices[count] = vector;
        count++;
        std::cout<<count;
    }
    
    if ( count >= MAX_VERTICES)
    {
        std::cout<<count;
        
    }
    
    fNumberOfVertices = count;
}
    
    
const Vector2D& Polygon ::  getVertex( size_t aIndex ) const
{
    return fVertices[aIndex];
   
}

    
float Polygon :: getPerimeter() const noexcept
{
    int i ;
    float length = 0.00;
    Vector2D vector;
//    std::cout<<"MAX VERTICES: "<<MAX_VERTICES;

    for (i = 0; i < fNumberOfVertices  ; i++)
        
    {
        int next_index = (i +1)% fNumberOfVertices;
        vector = fVertices[next_index] - fVertices[i];
        
        length += vector.length();
//        std::cout<<fVertices[i];

    }
    
    return length;
    
}

    
    

Polygon Polygon::  scale( float aScalar ) const noexcept
{
    int i ;
    Vector2D vector;
    Polygon Result = *this;
    
    for (i = 0; i < fNumberOfVertices  ; i++)
        
    {
        int next_index = (i +1)% fNumberOfVertices;
        vector = fVertices[i] * aScalar ;
        Result.fVertices[i] = vector;
        std::cout<<Result.fVertices[i];

    }
    
    return Result;
    
}
