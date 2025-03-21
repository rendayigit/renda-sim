// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/ContainerFull.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_CONTAINERFULL_H_
#define SMP_CONTAINERFULL_H_

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
    /// This exception is raised when trying to add a component to a container 
    /// that is full, i.e. where the Count has reached the Upper limit.
    class ContainerFull : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~ContainerFull() noexcept = default;

        /// Get the name of the full container.
        /// @return  Name of the full container.
        virtual Smp::String8 GetContainerName() const noexcept = 0;

        /// Get the size of the full container.
        /// @return  Size of the full container.
        virtual Smp::Int64 GetContainerSize() const noexcept = 0;
    };
}

#endif // SMP_CONTAINERFULL_H_
