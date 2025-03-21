// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IEventConsumer.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IEVENTCONSUMER_H_
#define SMP_IEVENTCONSUMER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IEventSink.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of an event consumer.
    /// An event sonsumer is a omponent that holds event sinks, which may be 
    /// subscribed to other component's event sources.
    /// 
    /// This is an optional interface. It needs to be implemented by components
    /// which want to allow access to event sinks by name.
    class IEventConsumer :
        public virtual Smp::IComponent
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IEventConsumer() noexcept = default;

        /// Query for the collection of all event sinks of the component.
        /// The collection may be empty if no event sinks exist.
        /// @return  Collection of event sinks.
        virtual const Smp::EventSinkCollection* GetEventSinks() const = 0;

        /// Query for an event sink of this component by its name.
        /// The returned event sink may be null if no event sink with the given
        /// name could be found.
        /// @param   name Event sink name.
        /// @return  Event sink with the given name, or null if no event sink 
        ///          with the given name could be found.
        virtual Smp::IEventSink* GetEventSink(
            Smp::String8 name) const = 0;
    };

}

#endif // SMP_IEVENTCONSUMER_H_
