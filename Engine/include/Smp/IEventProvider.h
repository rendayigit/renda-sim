// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IEventProvider.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IEVENTPROVIDER_H_
#define SMP_IEVENTPROVIDER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IEventSource.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of an event provider.
    /// An event provider is a omponent that holds event sources, which allow 
    /// other components to subscribe their event sinks.
    /// This is an optional interface. It needs to be implemented by components
    /// which want to allow access to event sources by name.
    class IEventProvider :
        public virtual Smp::IComponent
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IEventProvider() noexcept = default;

        /// Query for the collection of all event sources of the component.
        /// The collection may be empty if no event sources exist.
        /// @return  Collection of event sources.
        virtual const Smp::EventSourceCollection* GetEventSources() const = 0;

        /// Query for an event source of this component by its name.
        /// The returned event source may be null if no event source with the 
        /// given name could be found.
        /// @param   name Event source name.
        /// @return  Event source with the given name or null if no event 
        ///          source with the given name could be found.
        virtual Smp::IEventSource* GetEventSource(
            Smp::String8 name) const = 0;
    };

}

#endif // SMP_IEVENTPROVIDER_H_
