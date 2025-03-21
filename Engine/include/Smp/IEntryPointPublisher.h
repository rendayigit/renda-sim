// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IEntryPointPublisher.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IENTRYPOINTPUBLISHER_H_
#define SMP_IENTRYPOINTPUBLISHER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IEntryPoint.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of an entry point publisher.
    /// An entry point publisher is a component that publishes entry points.
    /// 
    /// @remarks The entry points may be registered, for example, with the 
    ///          Scheduler or the Event Manager services.
    ///          This is an optional interface. It needs to be implemented by 
    ///          components which want to provide access to their entry points 
    ///          by name.
    class IEntryPointPublisher :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IEntryPointPublisher() noexcept = default;

        /// Query for the collection of all entry points of the component.
        /// The collection may be empty if no entry points exist.
        /// @return  Collection of entry points.
        virtual const Smp::EntryPointCollection* GetEntryPoints() const = 0;

        /// Query for an entry point of this component by its name.
        /// The returned entry point may be null if no entry point with the 
        /// given name could be found.
        /// @param   name Entry point name.
        /// @return  Entry point with given name, or null if no entry point 
        ///          with given name could be found.
        virtual Smp::IEntryPoint* GetEntryPoint(
            Smp::String8 name) const = 0;
    };

}

#endif // SMP_IENTRYPOINTPUBLISHER_H_
