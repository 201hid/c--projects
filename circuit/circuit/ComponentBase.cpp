//
//  ComponentBase.cpp
//  circuit
//
//  Created by TOWHIDUL HASSAN on 10/4/2024.
//
#include "ComponentBase.h"
#include<assert.h>

ComponentBase :: ComponentBase(double aBaseValue,
              const std::string& aMajorUnit,
              const std::string& aMinorUnits ) noexcept:

    fBaseValue(aBaseValue),
    fMajorUnit(aMajorUnit),
    fMinorUnits(aMajorUnit)
{
    
    assert(aMajorUnit.size()>0 && aMinorUnits.size()>0 && aMajorUnit[0]==aMinorUnits[0]);
    
}

double ComponentBase:: getBaseValue() const noexcept
{
    return fBaseValue;
}

void ComponentBase:: setBaseValue( double aBaseValue ) noexcept
{
    fBaseValue = aBaseValue;
}

 const std::string& ComponentBase ::  getMajorUnit() const noexcept
{
    return fMajorUnit;
}

const std::string& ComponentBase ::  getMinorUnits() const noexcept
{
   return fMinorUnits;
}

double ComponentBase:: getPotentialAt( double aCurrent,
                       double aFrequency  ) const noexcept
{
    return aCurrent * getReactance(aFrequency);
}

double ComponentBase :: getCurrentAt( double aVoltage,
                     double aFrequency  ) const noexcept
{
    assert( aFrequency != 0);
    return aVoltage / getReactance(aFrequency);
}

 std::istream& operator>>( std::istream& aIStream, ComponentBase& aObject
{
    double lValue;
    std::string lUnit;
    
    aIStream >>lValue>>lUnit;
    
    
}

