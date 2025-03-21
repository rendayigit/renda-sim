// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/IScheduler.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_ISCHEDULER_H_
#define SMP_SERVICES_ISCHEDULER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IEntryPoint.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/Services/EventId.h"
#include "Smp/Services/InvalidCycleTime.h"
#include "Smp/Services/InvalidEventId.h"
#include "Smp/Services/InvalidEventTime.h"
#include "Smp/IService.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for simulation services
    namespace Services
    {
        /// This interface gives access to the Scheduler Service.
        /// Components can register (Add) and unregister (Remove) entry points 
        /// for scheduling. Further, they can set (Set) individual attributes 
        /// of events on the scheduler.
        /// The complete state of the Scheduler, with the exception of Events 
        /// scheduled using ZuluTime, shall be part of persisted data and 
        /// saved/restored to/from breakpoints.
        class IScheduler :
            public virtual Smp::IService
        {
        public:
            /// Name of the Scheduler service.
            static constexpr Smp::Char8 SMP_Scheduler[] = "Scheduler";
    

            /// Virtual destructor to release memory.
            virtual ~IScheduler() noexcept = default;

            /// Add an immediate event to the scheduler.
            /// An immediate event is an event that will be added as a 
            /// simulation time event (with simulation delta time of 0) at the 
            /// front of the event queue. As such, it will be executed when the
            /// scheduler processes its simulation time events again, but not 
            /// immediately in the call to AddImmediateEvent().
            /// When the simulator is in Standby state, simulation time does 
            /// not progress, and simulation time events (including immediate 
            /// events) are not processed.
            /// @remarks To execute an entry point immediately without going 
            ///          through the scheduler, its Execute() method can be 
            ///          called.
            /// @remarks For events scheduled at the same time (including 
            ///          immediate events), the Scheduler policy is to always 
            ///          execute those first that have been posted first 
            ///          ("First scheduled, first executed").
            /// @param   entryPoint Entry point to call from event.
            /// @return  Event identifier that can be used to change or remove 
            ///          event.
            virtual Smp::Services::EventId AddImmediateEvent(
                const Smp::IEntryPoint* entryPoint) = 0;

            /// Add event to scheduler that is called based on simulation time.
            /// An event with repeat=0 is not cyclic. It will be removed 
            /// automatically after is has been triggered.
            /// An event with repeat>0 is cyclic, and will be repeated 'repeat'
            /// times. Therefore, it will be called repeat+1 times, and then it
            /// will be removed automatically.
            /// An event with repeat=-1 is cyclic as well, but it will be 
            /// triggered forever, unless it is removed from the scheduler 
            /// using the RemoveEvent() method.
            /// For a cyclic event, the cycleTime needs to be positive. 
            /// Otherwise, an InvalidCycleTime exception is thrown. For 
            /// non-cyclic events, it is stored but not used.
            /// The simulationTime must not be negative. Otherwise, an 
            /// InvalidEventTime exception is thrown.
            /// @remarks For events scheduled at the same time (including 
            ///          immediate events), the Scheduler policy is to always 
            ///          execute those first that have been posted first 
            ///          ("First scheduled, first executed").
            /// @param   entryPoint Entry point to call from event.
            /// @param   simulationTime Duration from now when to trigger the 
            ///          event for the first time.
            ///          This must not be a negative simulation time, as this 
            ///          would be in the past.
            /// @param   cycleTime Duration between two triggers of the event.
            /// When repeat is not zero, this must be a positive duration.
            /// @param   repeat Number of times the event shall be repeated, or
            ///          0 for a single event, or -1 for no limit.
            /// @return  Event identifier that can be used to change or remove 
            ///          event.
            /// @throws  Smp::Services::InvalidCycleTime
            /// @throws  Smp::Services::InvalidEventTime
            virtual Smp::Services::EventId AddSimulationTimeEvent(
                const Smp::IEntryPoint* entryPoint,
                Smp::Duration simulationTime,
                Smp::Duration cycleTime = 0,
                Smp::Int64 repeat = 0) = 0;

            /// Add event to scheduler that is called based on mission time.
            /// An event with repeat=0 is not cyclic. It will be removed 
            /// automatically after is has been triggered.
            /// An event with repeat>0 is cyclic, and will be repeated repeat 
            /// times. Therefore, it will be called repeat+1 times, and then it
            /// will be removed automatically.
            /// An event with repeat=-1 is cyclic as well, but it will be 
            /// triggered forever, unless it is removed from the scheduler 
            /// using the RemoveEvent() method.
            /// For a cyclic event, the cycleTime needs to be positive. 
            /// Otherwise, an InvalidCycleTime exception is thrown. For 
            /// non-cyclic events, it is stored but not used.
            /// The missionTime must not be before the current mission time of 
            /// the ITimeKeeper service. Otherwise, an InvalidEventTime 
            /// exception is thrown.
            /// @remarks For events scheduled at the same time (including 
            ///          immediate events), the Scheduler policy is to always 
            ///          execute those first that have been posted first 
            ///          ("First scheduled, first executed").
            /// @param   entryPoint Entry point to call from event.
            /// @param   missionTime Absolute mission time when to trigger the 
            ///          event for the first time.
            /// This must not be a mission time in the past.
            /// @param   cycleTime Duration between two triggers of the event.
            /// When repeat is not zero, this must be a positive duration.
            /// @param   repeat Number of times the event shall be repeated, or
            ///          0 for a single event, or -1 for no limit.
            /// @return  Event identifier that can be used to change or remove 
            ///          event.
            /// @throws  Smp::Services::InvalidCycleTime
            /// @throws  Smp::Services::InvalidEventTime
            virtual Smp::Services::EventId AddMissionTimeEvent(
                const Smp::IEntryPoint* entryPoint,
                Smp::Duration missionTime,
                Smp::Duration cycleTime = 0,
                Smp::Int64 repeat = 0) = 0;

            /// Add event to scheduler that is called based on epoch time.
            /// An event with repeat=0 is not cyclic. It will be removed 
            /// automatically after is has been triggered.
            /// An event with repeat>0 is cyclic, and will be repeated repeat 
            /// times. Therefore, it will be called repeat+1 times, and then it
            /// will be removed automatically.
            /// An event with repeat=-1 is cyclic as well, but it will be 
            /// triggered forever, unless it is removed from the scheduler 
            /// using the RemoveEvent() method.
            /// For a cyclic event, the cycleTime needs to be positive. 
            /// Otherwise, an InvalidCycleTime exception is thrown. For 
            /// non-cyclic events, it is stored but not used.
            /// The epochTime must not be before the current epoch time of the 
            /// ITimeKeeper service. Otherwise, an InvalidEventTime exception 
            /// is thrown.
            /// @remarks For events scheduled at the same time (including 
            ///          immediate events), the Scheduler policy is to always 
            ///          execute those first that have been posted first 
            ///          ("First scheduled, first executed").
            /// @param   entryPoint Entry point to call from event.
            /// @param   epochTime Epoch time when to trigger the event for the
            ///          first time.
            /// This must not be an epoch time in the past.
            /// @param   cycleTime Duration between two triggers of the event.
            /// When repeat is not zero, this must be a positive duration.
            /// @param   repeat Number of times the event shall be repeated, or
            ///          0 for a single event, or -1 for no limit.
            /// @return  Event identifier that can be used to change or remove 
            ///          event.
            /// @throws  Smp::Services::InvalidCycleTime
            /// @throws  Smp::Services::InvalidEventTime
            virtual Smp::Services::EventId AddEpochTimeEvent(
                const Smp::IEntryPoint* entryPoint,
                Smp::DateTime epochTime,
                Smp::Duration cycleTime = 0,
                Smp::Int64 repeat = 0) = 0;

            /// Add event to scheduler that is called based on Zulu time.
            /// An event with repeat=0 is not cyclic. It will be removed 
            /// automatically after is has been triggered.
            /// An event with repeat>0 is cyclic, and will be repeated repeat 
            /// times. Therefore, it will be called repeat+1 times, and then it
            /// will be removed automatically.
            /// An event with repeat=-1 is cyclic as well, but it will be 
            /// triggered forever, unless it is removed from the scheduler 
            /// using the RemoveEvent() method.
            /// For a cyclic event, the cycleTime needs to be positive. 
            /// Otherwise, an InvalidCycleTime exception is thrown. For 
            /// non-cyclic events, it is stored but not used.
            /// The zuluTime must not be before the current Zulu time of the 
            /// ITimeKeeper service. Otherwise, an InvalidEventTime exception 
            /// is thrown.
            /// @remarks For events scheduled at the same time (including 
            ///          immediate events), the Scheduler policy is to always 
            ///          execute those first that have been posted first 
            ///          ("First scheduled, first executed").
            /// @param   entryPoint Entry point to call from event.
            /// @param   zuluTime Absolute (Zulu) time when to trigger the 
            ///          event for the first time.
            /// This must not be a time in the past.
            /// @param   cycleTime Duration between two triggers of the event.
            /// When repeat is not zero, this must be a positive duration.
            /// @param   repeat Number of times the event shall be repeated, or
            ///          0 for a single event, or -1 for no limit.
            /// @return  Event identifier that can be used to change or remove 
            ///          event.
            /// @throws  Smp::Services::InvalidCycleTime
            /// @throws  Smp::Services::InvalidEventTime
            virtual Smp::Services::EventId AddZuluTimeEvent(
                const Smp::IEntryPoint* entryPoint,
                Smp::DateTime zuluTime,
                Smp::Duration cycleTime = 0,
                Smp::Int64 repeat = 0) = 0;

            /// Update when an existing simulation time event on the scheduler 
            /// shall be triggered.
            /// When the given event Id is not a valid identifier of a 
            /// scheduler event, the method throws an exception of type 
            /// InvalidEventId. In case an event is registered under the given 
            /// event Id but it is not a simulation time event, the method 
            /// throws an exception of type InvalidEventId as well.
            /// 
            /// The simulationTime must not be negative. Otherwise, the event 
            /// will never be executed, but immediately removed.
            /// @param   event Identifier of event to modify.
            /// @param   simulationTime Duration from now when to trigger event.
            /// If the simulation time is negative, the event will never be 
            /// executed but instead be removed immediately from the scheduler.
            /// @throws  Smp::Services::InvalidEventId
            virtual void SetEventSimulationTime(
                Smp::Services::EventId event,
                Smp::Duration simulationTime) = 0;

            /// Update when an existing mission time event on the scheduler 
            /// shall be triggered.
            /// When the given event Id is not a valid identifier of a 
            /// scheduler event, the method throws an exception of type 
            /// InvalidEventId. In case an event is registered under the given 
            /// event Id but it is not a mission time event, the method throws 
            /// an exception of type InvalidEventId as well.
            /// 
            /// The missionTime must not be before the current mission time of 
            /// the ITimeKeeper service. Otherwise, the event will never be 
            /// executed, but immediately removed.
            /// @param   event Identifier of event to modify.
            /// @param   missionTime Absolute mission time when to trigger event.
            /// If the mission time is before the current mission time, the 
            /// event will never be executed but instead be removed immediately
            /// from the scheduler.
            /// @throws  Smp::Services::InvalidEventId
            virtual void SetEventMissionTime(
                Smp::Services::EventId event,
                Smp::Duration missionTime) = 0;

            /// Update when an existing epoch time event on the scheduler (an 
            /// event that has been registered using AddEpochTimeEvent()) shall
            /// be triggered.
            /// When the given event Id  is not a valid identifier of a 
            /// scheduler event, the method throws an exception of type 
            /// InvalidEventId. In case an event is registered under the given 
            /// event Id but it is not an epoch time event, the method throws 
            /// an exception of type InvalidEventId as well.
            /// 
            /// The epochTime must not be before the current epoch time of the 
            /// ITimeKeeper service. Otherwise, the event will never be 
            /// executed, but immediately removed.
            /// @param   event Identifier of event to modify.
            /// @param   epochTime Epoch time when to trigger event.
            /// If the epoch time is before the current epoch time, the event 
            /// will never be executed but instead be removed immediately from 
            /// the scheduler.
            /// @throws  Smp::Services::InvalidEventId
            virtual void SetEventEpochTime(
                Smp::Services::EventId event,
                Smp::DateTime epochTime) = 0;

            /// Update when an existing zulu time event on the scheduler shall 
            /// be triggered.
            /// When the given event Id is not a valid identifier of a 
            /// scheduler event, the method throws an exception of type 
            /// InvalidEventId. In case an event is registered under the given 
            /// event Id but it is not a zulu time event, the method throws an 
            /// exception of type InvalidEventId as well.
            /// The zuluTime must not be before the current Zulu time of the 
            /// ITimeKeeper service. Otherwise, the event will never be 
            /// executed, but immediately removed.
            /// @param   event Identifier of event to modify.
            /// @param   zuluTime Absolute (Zulu) time when to trigger event.
            /// If the zulu time is before the current zulu time, the event 
            /// will never be executed but instead be removed immediately from 
            /// the scheduler.
            /// @throws  Smp::Services::InvalidEventId
            virtual void SetEventZuluTime(
                Smp::Services::EventId event,
                Smp::DateTime zuluTime) = 0;

            /// Update cycle time of an existing event on the scheduler.
            /// When the given event is not a valid identifier of a scheduler 
            /// event, the method throws an exception of type InvalidEventId.
            /// For a cyclic event, the cycleTime needs to be positive. For 
            /// non-cyclic events, it is stored but not used.
            /// @param   event Identifier of event to modify.
            /// @param   cycleTime Duration between two triggers of the event.
            /// For a cyclic event, this needs to be a positive duration. 
            /// Otherwise, an exception of type InvalidCycleTime is thrown.
            /// @throws  Smp::Services::InvalidCycleTime
            /// @throws  Smp::Services::InvalidEventId
            virtual void SetEventCycleTime(
                Smp::Services::EventId event,
                Smp::Duration cycleTime) = 0;

            /// Update the repeat counter of an existing event on the 
            /// scheduler.
            /// When the given event is not a valid identifier of a scheduler 
            /// event, the method throws an exception of type InvalidEventId.
            /// An event with repeat=0 is not cyclic. It will be removed 
            /// automatically after is has been triggered.
            /// An event with repeat>0 is cyclic, and will be repeated 'repeat'
            /// times. Therefore, it will be called repeat+1 times, and then it
            /// will be removed automatically.
            /// An event with repeat=-1 is cyclic as well, but it will be 
            /// triggered forever, unless it is removed from the scheduler 
            /// using the RemoveEvent() method.
            /// For a cyclic event, the cycleTime needs to be positive. For 
            /// non-cyclic events, it is ignored.
            /// @param   event Identifier of event to modify.
            /// @param   repeat Number of times the event shall be repeated, or
            ///          0 for a single event, or -1 for no limit.
            ///          An event with a repeat different from 0 is called 
            ///          cyclic. For such an event, a positive cycle time has 
            ///          to be defined before. Otherwise, an exception of type 
            ///          InvalidCycleTime is thrown.
            /// @throws  Smp::Services::InvalidEventId
            virtual void SetEventRepeat(
                Smp::Services::EventId event,
                Smp::Int64 repeat) = 0;

            /// Remove an event from the scheduler.
            /// When the given event is not a valid identifier of a scheduler 
            /// event, the method throws an exception of type InvalidEventId.
            /// An event with repeat=0 is removed automatically after it has 
            /// been triggered.
            /// @param   event Event identifier of the event to remove.
            /// @throws  Smp::Services::InvalidEventId
            virtual void RemoveEvent(
                Smp::Services::EventId event) = 0;

            /// Return the ID of the event currently executed by the scheduler.
            /// If not event is executed, this function returns -1.
            /// The operation returns -1 when no event is being executed.
            /// @return  Event Id or -1 if no event is being executed.
            virtual Smp::Services::EventId GetCurrentEventId() const = 0;

            /// Get the time of next scheduled Event.
            /// This function can only provide the time of the next event at 
            /// the time of invocation. There is no guarantee that no events 
            /// will be inserted between the method invocation and the 
            /// (currently) next event.
            /// Events scheduled in Zulu Time are not considered, as these 
            /// Events do not have a fixed defined Simulation Time.
            /// @return  Time of the next event on the scheduler.
            virtual Smp::Duration GetNextScheduledEventTime() const = 0;
        };
    }
}

#endif // SMP_SERVICES_ISCHEDULER_H_
