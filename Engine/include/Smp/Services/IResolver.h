// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/Services/IResolver.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_SERVICES_IRESOLVER_H_
#define SMP_SERVICES_IRESOLVER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IComponent.h"
#include "Smp/IObject.h"
#include "Smp/PrimitiveTypes.h"
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
        /// This interface gives access to the Resolver Service.
        class IResolver :
            public virtual Smp::IService
        {
        public:
            /// Name of the Resolver service.
            static constexpr Smp::Char8 SMP_Resolver[] = "Resolver";
    

            /// Virtual destructor to release memory.
            virtual ~IResolver() noexcept = default;

            /// Resolve reference to an object via absolute path.
            /// An absolute path contains the name of either a Model or 
            /// Service, but not the name of the simulator, although the 
            /// simulator itself is the top-level object. This allows keeping 
            /// names as short as possible, and avoids a dependency on the name
            /// of the simulator itself.
            /// @param   absolutePath Absolute path to object in simulation.
            /// @return  Object identified by path, or null if no object with 
            ///          the given path could be found.
            virtual Smp::IObject* ResolveAbsolute(
                Smp::String8 absolutePath) = 0;

            /// Resolve reference to an object via relative path.
            /// @param   relativePath Relative path to object in simulation.
            /// @param   sender Component that asks for resolving the reference.
            /// @return  Component identified by path, or null if no component 
            ///          with the given path could be found.
            virtual Smp::IObject* ResolveRelative(
                Smp::String8 relativePath,
                const Smp::IComponent* sender) = 0;
        };
    }
}

#endif // SMP_SERVICES_IRESOLVER_H_
