#include "Vector3D.h"
#include <iomanip>
#include <sstream>
#include <cmath>

#include <sstream>
#include <cmath>
#include <iomanip>

std::string Vector3D::toString() const noexcept {
    std::ostringstream lStream;
    lStream << "[";

    auto lFormatCoordinate = [&lStream](float aCoordinate) {
        std::stringstream ltempStream;
        if (std::floor(aCoordinate) == aCoordinate) {
            lStream << static_cast<int>(aCoordinate);
        } else {
            ltempStream << std::fixed << std::setprecision((std::abs(aCoordinate) < 10000) ? 4 : 1) << aCoordinate;
            std::string str = ltempStream.str();
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            if (str.back() == '.') {
                str.pop_back();
            }
            lStream << str;
        }
    };

    lFormatCoordinate(x());
    lStream << ",";
    lFormatCoordinate(y());
    lStream << ",";
    lFormatCoordinate(w());

    lStream << "]";
    return lStream.str();
}
