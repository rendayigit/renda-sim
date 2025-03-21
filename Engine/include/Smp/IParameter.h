// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IParameter.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IPARAMETER_H_
#define SMP_IPARAMETER_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/ICollection.h"
#include "Smp/Publication/IType.h"
#include "Smp/Publication/ParameterDirectionKind.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This interface describes a parameter of a published operation.
    class IParameter :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IParameter() noexcept = default;

        /// Provides the type of the parameter.
        /// @return  Type of the parameter.
        virtual Smp::Publication::IType* GetType() const = 0;

        /// Provides the parameter direction kind of the parameter.
        /// @return  Parameter direction kind of the parameter.
        virtual Smp::Publication::ParameterDirectionKind GetDirection() const = 0;
    };

    /// A parameter collection is an ordered collection of parameters, which 
    /// allows iterating all members.
    typedef Smp::ICollection<IParameter> ParameterCollection;

}

#endif // SMP_IPARAMETER_H_
