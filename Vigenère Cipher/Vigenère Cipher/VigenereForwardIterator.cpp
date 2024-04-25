//#include <cctype>
//#include "VigenereForwardIterator.h"
//
//VigenereForwardIterator::VigenereForwardIterator(const std::string& aKeyword, const std::string& aSource, EVigenereMode aMode) noexcept :
//        fMode(aMode),
//        fKeys(aKeyword, aSource),
//        fSource(aSource),
//        fIndex(-1),
//        fCurrentChar(NULL)
//{
//    initializeTable();
//}
//
//char VigenereForwardIterator:: operator*() const noexcept
//{
//    return fCurrentChar;
//}
//
//VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept{
//
//    fIndex++;
//    if( fIndex>= fSource.length()){
//        return *this;
//    }
//    
//    else if(std::isalpha(fSource[fIndex]))
//    {
//        if (fMode== EVigenereMode:: Encode){
//            encodeCurrentChar();
//        }
//        else{
//            decodeCurrentChar();
//        }
//    }
//    
//    else
//    {
//        fCurrentChar= fSource[fIndex];
//    }
//    return *this;
//    
//}
//
//VigenereForwardIterator VigenereForwardIterator ::operator++(int) noexcept{
//    VigenereForwardIterator copy = *this;
//    ++(*this);
//    return copy;
//}
//
//bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
//    return fIndex == aOther.fIndex && &fSource == &aOther.fSource;
//}
//
//bool VigenereForwardIterator ::operator!=(const VigenereForwardIterator& aOther) const noexcept
//{
//    return !(*this==aOther);
//}
//
//
//VigenereForwardIterator VigenereForwardIterator::begin() const noexcept
//{
//    VigenereForwardIterator copy(*this);
//    copy.fIndex = -1;  // Ensures that the iterator starts before the first character
//    ++temp;  // Initialize to the first character immediately
//    return temp;
//}


#include <cctype>
#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(const std::string& aKeyword, const std::string& aSource, EVigenereMode aMode) noexcept :
        fMode(aMode),
        fKeys(aKeyword, aSource),
        fSource(aSource),
        fIndex(-1),
        fCurrentChar('\0')
{
    initializeTable();
}

char VigenereForwardIterator::operator*() const noexcept {
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++() noexcept {
    ++fIndex;
    if (fIndex >= fSource.length()){
        return *this;
    }

    if (std::isalpha(fSource[fIndex])) {
        if (fMode == EVigenereMode::Encode)
            encodeCurrentChar();
        else
            decodeCurrentChar();

        ++fKeys;
    }
    else {
        fCurrentChar = fSource[fIndex];
    }

    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int) noexcept {
    VigenereForwardIterator temp = *this;
    ++(*this);
    return temp;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const noexcept {
        return fIndex == aOther.fIndex && &fSource == &aOther.fSource;
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const noexcept {
    return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const noexcept {
    VigenereForwardIterator it(*this);
    it.fIndex = -1;  // Reset index to the initial state
    ++it;  // Position it at the first valid character
    return it;
}

VigenereForwardIterator VigenereForwardIterator::end() const noexcept {
    VigenereForwardIterator result = *this;
    result.fIndex = fSource.length();
    return result;
}

void VigenereForwardIterator::encodeCurrentChar() noexcept {
    char sourceChar = fSource[fIndex];
    char keyChar = std::toupper(*fKeys);

    if (std::isalpha(sourceChar)) {
        char encodedChar = fMappingTable[std::toupper(keyChar) - 'A'][std::toupper(sourceChar) - 'A'];
        if (std::islower(sourceChar)) {
            encodedChar = std::tolower(encodedChar);
        }
        fCurrentChar = encodedChar;
    } else {
        fCurrentChar = sourceChar; // Non-alphabetic characters remain unchanged
    }
}

void VigenereForwardIterator::decodeCurrentChar() noexcept {
    char sourceChar = fSource[fIndex];
    char keyChar = std::toupper(*fKeys);

    if (std::isalpha(sourceChar)) {
        char decodedChar = 'A';
        if (std::isupper(sourceChar)) {
            for (int i = 0; i < CHARACTERS; ++i) {
                if (fMappingTable[keyChar - 'A'][i] == std::toupper(sourceChar)) {
                    decodedChar = 'A' + i;
                    break;
                }
            }
        } else if (std::islower(sourceChar)) {
            for (int i = 0; i < CHARACTERS; ++i) {
                if (fMappingTable[keyChar - 'A'][i] == std::toupper(sourceChar)) {
                    decodedChar = 'a' + i;
                    break;
                }
            }
        }
        fCurrentChar = decodedChar;
    } else {
        fCurrentChar = sourceChar;
    }
}
