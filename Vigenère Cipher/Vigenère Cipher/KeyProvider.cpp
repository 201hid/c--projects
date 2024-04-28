//
//  KeyProvider.cpp
//  Vigenère Cipher
//  Created by TOWHIDUL HASSAN on 24/4/2024.
//

#include <stdio.h>
#include "KeyProvider.h"
#include <cctype>
#include <cassert>

std::string KeyProvider::preprocessString(const std::string& aString) noexcept {
    std::string lResult;
    for (char c : aString) {
        if (std::isalpha(c)) {
            lResult += std::toupper(c);
        }
    }
    return lResult;
}

KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept {
    std::string lPreprocessedKeyword = preprocessString(aKeyword);
    std::string lPreprocessedSource = preprocessString(aSource);
    fKeys = "";

    while (fKeys.length() < lPreprocessedSource.length()) {
        fKeys += lPreprocessedKeyword;
    }
    fKeys = fKeys.substr(0, lPreprocessedSource.length());
    fIndex = 0;
    assert(fKeys.length() == lPreprocessedSource.length());
}

char KeyProvider::operator*() const noexcept {
    assert(fIndex < fKeys.length());
    return fKeys[fIndex];
}

KeyProvider& KeyProvider::operator++() noexcept {
    fIndex++;
    return *this;
}

KeyProvider KeyProvider::operator++(int) noexcept {
    KeyProvider lCopy = *this;
    ++(*this);
    return lCopy;
}

bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept {
    return fKeys == aOther.fKeys && fIndex == aOther.fIndex;
}

bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept {
    return !(*this == aOther);
}

KeyProvider KeyProvider::begin() const noexcept {
    KeyProvider lCopy = *this;
    lCopy.fIndex = 0;
    return lCopy;
}

KeyProvider KeyProvider::end() const noexcept {
    KeyProvider lCopy = *this;
    lCopy.fIndex = fKeys.length();
    return lCopy;
}
