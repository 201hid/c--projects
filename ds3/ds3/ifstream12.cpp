#include "ifstream12.h"
#include <iostream>

ifstream12::ifstream12(const char* aFileName, size_t aBufferSize)
    : fBufferSize(aBufferSize), fBuffer(new std::byte[aBufferSize]), fByteIndex(0), fBitIndex(7), fByteCount(0) {
    if (aFileName) {
        open(aFileName);
    }
}

ifstream12::~ifstream12() {
    close();
    delete[] fBuffer;
}

void ifstream12::open(const char *aFileName) {
    fIStream.open(aFileName, std::ios::binary);
    if (fIStream) {
        fetch_data();
    } else {
        std::cerr << "Failed to open file: " << aFileName << std::endl;
    }
}

void ifstream12::close() {
    if (fIStream.is_open()) {
        fIStream.close();
    }
}

bool ifstream12::isOpen() const {
    return fIStream.is_open();
}

bool ifstream12::good() const {
    return fIStream.good() && !eof();
}

bool ifstream12::eof() const {
    return fByteIndex >= fByteCount && fIStream.eof();
}

void ifstream12::reset() {
    std::fill(fBuffer, fBuffer + fBufferSize, std::byte{0});
    fByteCount = 0;
    fByteIndex = 0;
    fBitIndex = 7;
}

void ifstream12::fetch_data() {
    if (!fIStream.eof()) {
        fIStream.read(reinterpret_cast<char*>(fBuffer), fBufferSize);
        fByteCount = fIStream.gcount();
        fByteIndex = 0;
        fBitIndex = 7;
    }
}

std::optional<size_t> ifstream12::readBit() {
    if (fByteIndex >= fByteCount && !fIStream.eof()) {
        fetch_data();
    }
    if (fByteIndex >= fByteCount) {
        return std::nullopt;
    }

    size_t bit = (size_t)((fBuffer[fByteIndex] >> fBitIndex) & std::byte{1});
    if (--fBitIndex < 0) {
        fBitIndex = 7;
        fByteIndex++;
    }

    return bit;
}

ifstream12& ifstream12::operator>>(size_t& aValue) {
    aValue = 0;
    size_t bitsRead = 0;
    while (bitsRead < 12) {
        auto bit = readBit();
        if (!bit.has_value()) {
            break;
        }
        if (bit.value() == 1) {
            aValue |= (1ULL << bitsRead);
        }
        bitsRead++;
    }
    return *this;
}
