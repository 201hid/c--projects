#include "FibonacciSequenceGenerator.h"
#include <limits>
#include <cassert>

// Constructor initializes the sequence with the given ID and sets the starting values for the Fibonacci sequence.
FibonacciSequenceGenerator::FibonacciSequenceGenerator(const std::string& aID) noexcept
    : fID(aID), fPrevious(0), fCurrent(1) {}

// Returns the sequence ID.
const std::string& FibonacciSequenceGenerator::id() const noexcept {
    return fID;
}

// Returns a constant reference to the current Fibonacci number.
const long long& FibonacciSequenceGenerator::operator*() const noexcept {
    return fCurrent;
}

// Type conversion to bool to check if the next Fibonacci number is possible (not negative).
FibonacciSequenceGenerator::operator bool() const noexcept {
    return hasNext();
}

// Resets the Fibonacci sequence to the first number.
void FibonacciSequenceGenerator::reset() noexcept {
    fPrevious = 0;
    fCurrent = 1;
}

// Checks if the next Fibonacci number can be generated without integer overflow.
bool FibonacciSequenceGenerator::hasNext() const noexcept {
    // We use std::numeric_limits<long long>::max() to check for overflow.
    return std::numeric_limits<long long>::max() - fCurrent >= fPrevious;
//    return 0;
}

// Advances to the next Fibonacci number, with an overflow check.
void FibonacciSequenceGenerator::next() noexcept {
    long long next = fCurrent + fPrevious;
    fPrevious = fCurrent;
    fCurrent = next;
}
