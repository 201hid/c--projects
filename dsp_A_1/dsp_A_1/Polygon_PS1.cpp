#include "Polygon.h"
#include <cassert>

float Polygon::getSignedArea() const noexcept {
    float lArea = 0.0f;
    for (int i = 0; i < fNumberOfVertices; i++) {
        int lNextVertex = (i + 1) % fNumberOfVertices;
        lArea += (fVertices[i].y() + fVertices[lNextVertex].y()) * (fVertices[i].x() - fVertices[lNextVertex].x());
    }
    return lArea / 2.0f;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    Polygon lResult = *this;
    for (int i = 0; i < fNumberOfVertices; i++) {
        Vector3D lTransformedVertex = aMatrix * Vector3D(fVertices[i].x(), fVertices[i].y(), 1);
        lResult.fVertices[i] = Vector2D(lTransformedVertex.x(), lTransformedVertex.y());
    }
    return lResult;
}
