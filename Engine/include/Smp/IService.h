// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IService.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_ISERVICE_H_
#define SMP_ISERVICE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "ICollection.h"
#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for a service.
    /// @remarks Currently, this interface does not add any functionality.
    class IService :
        public virtual Smp::IComponent
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IService() noexcept = default;

    };

    /// A service collection is an ordered collection of services, which allows
    /// iterating all members.
    typedef Smp::ICollection<IService> ServiceCollection;
}

#endif // SMP_ISERVICE_H_
