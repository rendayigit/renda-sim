// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/ISimpleArrayField.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_ISIMPLEARRAYFIELD_H_
#define SMP_ISIMPLEARRAYFIELD_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/AnySimple.h"
#include "Smp/AnySimpleArray.h"
#include "Smp/InvalidArrayIndex.h"
#include "Smp/InvalidArraySize.h"
#include "Smp/InvalidArrayValue.h"
#include "Smp/InvalidFieldValue.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IArrayField.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface to an array where each array item is of a simple type.
    class ISimpleArrayField :
        public virtual Smp::IField
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~ISimpleArrayField() noexcept = default;

        /// Get the size (number of array items) of the field.
        /// @return  Size (number of array items) of the field.
        virtual Smp::UInt64 GetSize() const = 0;

        /// Get a value from a specific index of the array field.
        /// This method raises an exception of type InvalidIndex if called with
        /// an index value beyond the size of the array.
        /// @param   index Index of value to get.
        /// @return  Value from given index.
        /// @throws  Smp::InvalidArrayIndex
        virtual Smp::AnySimple GetValue(
            Smp::UInt64 index) const = 0;

        /// Set a value at given index of the array field.
        /// This method raises an exception of type InvalidFieldValue if called
        /// with an invalid value and an exception of type InvalidIndex if 
        /// called with an index value beyond the size of the array.
        /// @param   index Index of value to set.
        /// @param   value Value to set at given index.
        /// @throws  Smp::InvalidArrayIndex
        /// @throws  Smp::InvalidFieldValue
        virtual void SetValue(
            Smp::UInt64 index,
            Smp::AnySimple value) = 0;

        /// Get all values of the array field.
        /// This method raises an exception of type InvalidArraySize if called 
        /// with an array of wrong size.
        /// The array with the values has to be pre-allocated by the caller, 
        /// and has to be released by the caller as well. Therefore, an inout 
        /// parameter is used, not a return value of the method.
        /// @param   length Size of given values array.
        /// @param   values Pre-allocated array of values to store result to.
        /// @throws  Smp::InvalidArraySize
        virtual void GetValues(
            Smp::UInt64 length,
            Smp::AnySimpleArray values) const = 0;

        /// Set all values of the array field.
        /// This method raises an exception of type InvalidArraySize if called 
        /// with an array of wrong size and an exception of type 
        /// InvalidArrayValue if called with an invalid values array.
        /// @param   length Size of given values array.
        /// @param   values Array of values to store in array field.
        /// @throws  Smp::InvalidArraySize
        /// @throws  Smp::InvalidArrayValue
        virtual void SetValues(
            Smp::UInt64 length,
            Smp::AnySimpleArray values) = 0;
    };
}

#endif // SMP_ISIMPLEARRAYFIELD_H_
