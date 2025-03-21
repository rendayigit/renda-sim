// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/TimeKind.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_TIMEKIND_H_
#define SMP_SERVICES_TIMEKIND_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/PrimitiveTypes.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Namespace for simulation services
    namespace Services
    {
        /// Enumeration of supported time kinds.
        enum class TimeKind : Smp::Int32
        {
            /// Simulation time.
            TK_SimulationTime,

            /// Mission time.
            TK_MissionTime,

            /// Epoch time.
            TK_EpochTime,

            /// Zulu time.
            TK_ZuluTime
        };

        /// Stream operator for TimeKind to be able to print an enum value.
        /// @param os Output stream to output to.
        /// @param obj Object to output to stream.
        std::ostream& operator << (std::ostream& os, const TimeKind& obj);
    }
}

#endif // SMP_SERVICES_TIMEKIND_H_
