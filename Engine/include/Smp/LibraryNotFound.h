// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/LibraryNotFound.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_LIBRARYNOTFOUND_H_
#define SMP_LIBRARYNOTFOUND_H_

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
    /// exist.
    class LibraryNotFound : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~LibraryNotFound() noexcept = default;

        /// Get the file name of the library that is invalid.
        /// @return  Fully qualified field name that is invalid.
        virtual Smp::String8 GetLibraryName() const noexcept = 0;
    };
}

#endif // SMP_LIBRARYNOTFOUND_H_
