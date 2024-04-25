//
//  KeyProvider.cpp
//  Vigenère Cipher
//
//  Created by TOWHIDUL HASSAN on 24/4/2024.
//

#include <stdio.h>
#include "KeyProvider.h"
#include <cctype>
#include <cassert>

std::string KeyProvider:: preprocessString(const std::string& aString) noexcept{
    std::string result;
    for (char c: aString ){
        if (std::isalpha(c))
        {
            result +=std::toupper(c);
        }
    }
    return result;
    
}

KeyProvider :: KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept
{
    std::string preprocessedKeyword = preprocessString(aKeyword);
    std::string preprocessedSource = preprocessString(aSource);
    fKeys ="";

    while(fKeys.length()<preprocessedSource.length())
    {
        fKeys += preprocessedKeyword;
    }
    fKeys = fKeys.substr(0,preprocessedSource.length() );
    fIndex=0;
    assert(fKeys.length() == preprocessedSource.length());

}


char KeyProvider:: operator*() const noexcept{
//    assert(fIndex < fKeys.length());
    return fKeys[fIndex];
}

KeyProvider& KeyProvider::operator++() noexcept
{
    fIndex++;
    return *this;
}

KeyProvider KeyProvider:: operator++(int) noexcept
{
    KeyProvider copy = *this;
    ++(*this);
    return copy;
}

bool KeyProvider:: operator==(const KeyProvider& aOther) const noexcept
{
    if( fKeys == aOther.fKeys && fIndex == aOther.fIndex)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool KeyProvider :: operator!=(const KeyProvider& aOther) const noexcept
{
    if (*this==aOther)
    {
        return false;
    }
    else
    {
        return true;
    }

}

KeyProvider KeyProvider:: begin() const noexcept
{
    KeyProvider copy = *this;
    copy.fIndex=0;
    return copy;
}

KeyProvider KeyProvider:: end() const noexcept
{
    KeyProvider copy = *this;
    copy.fIndex = fKeys.length();
    return copy;
}
