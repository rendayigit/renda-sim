// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IEventSource.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IEVENTSOURCE_H_
#define SMP_IEVENTSOURCE_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/EventSinkAlreadySubscribed.h"
#include "Smp/EventSinkNotSubscribed.h"
#include "Smp/ICollection.h"
#include "Smp/IEventSink.h"
#include "Smp/InvalidEventSink.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface of an event source that event sinks (IEventSink) can 
    /// subscribe to.
    /// This interface allows event consumers to subscribe to or unsubscribe 
    /// from an event.
    class IEventSource :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IEventSource() noexcept = default;

        /// Subscribe to the event source, i.e. request notifications.
        /// If the given event sink is already subscribed to the event source, 
        /// an exception of type EventSinkAlreadySubscribed is thrown.
        /// If the type of the event argument of the event sink is not the type
        /// the event source expects, an exception of type InvalidEventSink is 
        /// thrown.
        /// An event sink can only be subscribed once to each event source. 
        /// Event sinks will be called in the order they have been subscribed 
        /// to the event source.
        /// @param   eventSink Event sink to subscribe to event source.
        /// @throws  Smp::EventSinkAlreadySubscribed
        /// @throws  Smp::InvalidEventSink
        virtual void Subscribe(
            Smp::IEventSink* eventSink) = 0;

        /// Unsubscribe from the event source, i.e. cancel notifications.
        /// This method raises the EventSinkNotSubscribed exception if the 
        /// given event sink is not subscribed to the event source.
        /// An event sink can only be unsubscribed if it has been subscribed 
        /// before.
        /// @param   eventSink Event sink to unsubscribe from event source.
        /// @throws  Smp::EventSinkNotSubscribed
        virtual void Unsubscribe(
            Smp::IEventSink* eventSink) = 0;
    };

    /// An event source collection is an ordered collection of event sources, 
    /// which allows iterating all members.
    typedef Smp::ICollection<IEventSource> EventSourceCollection;

}

#endif // SMP_IEVENTSOURCE_H_
