// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidLibrary.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDLIBRARY_H_
#define SMP_INVALIDLIBRARY_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is raised when trying to load a library that does not 
    /// contain an Initialise() function.
    class InvalidLibrary : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidLibrary() noexcept = default;

        /// Get the file name of the library that is invalid.
        /// @return  Fully qualified field name that is invalid.
        virtual Smp::String8 GetLibraryName() const noexcept = 0;
    };
}

#endif // SMP_INVALIDLIBRARY_H_
