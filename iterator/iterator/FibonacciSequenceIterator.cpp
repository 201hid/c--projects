#include "FibonacciSequenceIterator.h"
#include <iostream>

FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequenceGenerator& aSeqObject, long long aStartIndex) noexcept
    : fSequenceObject(aSeqObject), fIndex(aStartIndex) {
    for (long long i = 1; i < fIndex; i++) {
        fSequenceObject.next();
    }
}

const long long& FibonacciSequenceIterator::operator*() const noexcept {
    return *fSequenceObject;
}

FibonacciSequenceIterator& FibonacciSequenceIterator::operator++() noexcept {
    fSequenceObject.next();
    fIndex++;
    return *this;
}

FibonacciSequenceIterator FibonacciSequenceIterator::operator++(int) noexcept {
    FibonacciSequenceIterator lCopy = *this;
    ++(*this);
    return lCopy;
}

bool FibonacciSequenceIterator::operator==(const FibonacciSequenceIterator& aOther) const noexcept {
    return this->fIndex == aOther.fIndex && fSequenceObject.id() == aOther.fSequenceObject.id();
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const noexcept {
    return !(*this == aOther);
}

FibonacciSequenceIterator FibonacciSequenceIterator::begin() const noexcept {
    return FibonacciSequenceIterator(fSequenceObject);
}

FibonacciSequenceIterator FibonacciSequenceIterator::end() const noexcept {
    FibonacciSequenceIterator lEndIterator = *this;
    while (lEndIterator.fSequenceObject.hasNext()) {
        lEndIterator++;
    }

    return ++lEndIterator;

}
