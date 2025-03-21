// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/CannotDelete.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_CANNOTDELETE_H_
#define SMP_CANNOTDELETE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/IComponent.h"
#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is thrown when trying to delete a component from a 
    /// container when the number of contained components is lower than or 
    /// equal to the Lower limit.
    class CannotDelete : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~CannotDelete() noexcept = default;

        /// Get the name of the container.
        /// @return  Name of the container.
        virtual Smp::String8 GetContainerName() const noexcept = 0;

        /// Get the Component that could not be deleted.
        /// @return  Component that could not be deleted.
        virtual const Smp::IComponent* GetComponent() const noexcept = 0;

        /// Get the lower limit of the container.
        /// @return  Lower limit of the container.
        virtual Smp::Int64 GetLowerLimit() const noexcept = 0;
    };

}

#endif // SMP_CANNOTDELETE_H_
