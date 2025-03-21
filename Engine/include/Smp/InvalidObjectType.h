// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/InvalidObjectType.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_INVALIDOBJECTTYPE_H_
#define SMP_INVALIDOBJECTTYPE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exception.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This exception is raised when trying to pass an object of wrong type.
    /// @remarks This can happen when adding a component to a container or 
    ///          reference which is semantically typed by a specific type 
    ///          implementing IComponent.
    class InvalidObjectType : public virtual Smp::Exception
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~InvalidObjectType() noexcept = default;

        /// Get the object that is not of valid type.
        /// @return  Object that is not of valid type.
        virtual const Smp::IObject* GetInvalidObject() const noexcept = 0;
    };

}

#endif // SMP_INVALIDOBJECTTYPE_H_
