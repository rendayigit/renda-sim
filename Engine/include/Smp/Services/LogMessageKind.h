// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/LogMessageKind.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_LOGMESSAGEKIND_H_
#define SMP_SERVICES_LOGMESSAGEKIND_H_

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

        /// This type is used as identifier of a log message kind.
        typedef Smp::Int32 LogMessageKind;
    }
}

#endif // SMP_SERVICES_LOGMESSAGEKIND_H_
