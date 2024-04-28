
//  VigenereForwardIterator.cpp
//  Vigenère Cipher
//  Created by TOWHIDUL HASSAN on 25/4/2024.


#include <cctype>
#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(const std::string& aKeyword, const std::string& aSource, EVigenereMode aMode) noexcept
    : fMode(aMode), fKeys(aKeyword, aSource), fSource(aSource), fIndex(-1), fCurrentChar() {
    initializeTable();
}

char VigenereForwardIterator::operator*() const noexcept {
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept {
    ++fIndex;
    if (fIndex >= fSource.length()) {
        return *this;
    } else if (std::isalpha(fSource[fIndex])) {
        if (fMode == EVigenereMode::Encode) {
            encodeCurrentChar();
        } else {
            decodeCurrentChar();
        }
        ++fKeys;
    } else {
        fCurrentChar = fSource[fIndex];
    }
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept {
    VigenereForwardIterator lCopy = *this;
    ++(*this);
    return lCopy;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
    if (fIndex == aOther.fIndex && fSource[fIndex] == aOther.fSource[fIndex]) {
        return true;
    } else {
        return false;
    }
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept {
    if (*this == aOther) {
        return false;
    } else {
        return true;
    }
}

VigenereForwardIterator VigenereForwardIterator::begin() const noexcept {
    VigenereForwardIterator lIterator(*this);
    lIterator.fIndex = -1;
    ++lIterator;
    return lIterator;
}

VigenereForwardIterator VigenereForwardIterator::end() const noexcept {
    VigenereForwardIterator lCopy = *this;
    lCopy.fIndex = fSource.length();
    return lCopy;
}

void VigenereForwardIterator::encodeCurrentChar() noexcept {
    char lSourceChar = fSource[fIndex];
    char lKeyChar = *fKeys;

    if (std::isalpha(lSourceChar)) {
        char lEncodedChar = fMappingTable[lKeyChar - 'A'][std::toupper(lSourceChar) - 'A'];
        if (std::islower(lSourceChar)) {
            lEncodedChar = std::tolower(lEncodedChar);
        }
        fCurrentChar = lEncodedChar;
    } else {
        fCurrentChar = lSourceChar;
    }
}

void VigenereForwardIterator::decodeCurrentChar() noexcept {
    char lSourceChar = fSource[fIndex];
    char lKeyChar = *fKeys;

    if (std::isalpha(lSourceChar)) {
        char lDecodedChar = 'A'; // Default to 'A' to ensure it's an uppercase result by default
        if (std::isupper(lSourceChar)) {
            for (int lI = 0; lI < CHARACTERS; ++lI) {
                if (fMappingTable[lKeyChar - 'A'][lI] == std::toupper(lSourceChar)) {
                    lDecodedChar = 'A' + lI;
                    break;
                }
            }
        } else if (std::islower(lSourceChar)) {
            for (int lI = 0; lI < CHARACTERS; ++lI) {
                if (fMappingTable[lKeyChar - 'A'][lI] == std::toupper(lSourceChar)) {
                    lDecodedChar = 'a' + lI;
                    break;
                }
            }
        }
        fCurrentChar = lDecodedChar;
    } else {
        fCurrentChar = lSourceChar;
    }
}
