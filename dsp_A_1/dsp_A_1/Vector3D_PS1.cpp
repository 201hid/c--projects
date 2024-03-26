
// COS30008, tutorial 3, 2024

#include "Vector3D.h"
#include <iomanip> // Include for std::setprecision
#include <sstream>
#include <cassert>
#include <cmath>



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



