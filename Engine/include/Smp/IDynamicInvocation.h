// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IDynamicInvocation.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IDYNAMICINVOCATION_H_
#define SMP_IDYNAMICINVOCATION_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/IOperation.h"
#include "Smp/IProperty.h"
#include "Smp/IRequest.h"
#include "Smp/InvalidOperationName.h"
#include "Smp/InvalidParameterCount.h"
#include "Smp/InvalidParameterType.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/IComponent.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// Interface for a component that supports dynamic invocation of 
    /// operations.
    /// @remarks Dynamic invocation is typically used for scripting.
    /// A component may implement this interface in order to allow dynamic 
    /// invocation of its operations.
    class IDynamicInvocation :
        public virtual Smp::IComponent
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IDynamicInvocation() noexcept = default;

        /// Return a request object for the given operation that describes the 
        /// parameters and the return value.
        /// The request object may be null if no operation with the given name 
        /// could be found, or if the operation with the given name does not 
        /// support dynamic invocation.
        /// @param   operationName Name of operation.
        /// @return  Request object for operation, or null if either no 
        ///          operation with the given name could be found, or the 
        ///          operation with the given name does not support dynamic 
        ///          invocation.
        virtual Smp::IRequest* CreateRequest(
            Smp::String8 operationName) = 0;

        /// Dynamically invoke an operation using a request object that has 
        /// been created and filled with parameter values by the caller.
        /// @remarks The same request object can be used to invoke a method 
        ///          several times.
        ///          This method raises the InvalidOperationName exception if 
        ///          the request object passed does not name an operation that 
        ///          allows dynamic invocation. When calling invoke with a 
        ///          wrong number of parameters, the InvalidParameterCount 
        ///          exception is raised. When passing a parameter of wrong 
        ///          type, the InvalidParameterType exception is raised.
        /// @param   request Request object to invoke.
        /// @throws  Smp::InvalidOperationName
        /// @throws  Smp::InvalidParameterCount
        /// @throws  Smp::InvalidParameterType
        virtual void Invoke(
            Smp::IRequest* request) = 0;

        /// Destroy a request object that has been created with the 
        /// CreateRequest() method before.
        /// The request object must not be used anymore after DeleteRequest() 
        /// has been called for it.
        /// @param   request Request object to destroy.
        virtual void DeleteRequest(
            Smp::IRequest* request) = 0;

        /// Provides the collection of properties that have been published.
        /// @return  Collection of properties that have been published, which 
        ///          may be empty.
        virtual const Smp::PropertyCollection* GetProperties() const = 0;

        /// Provides the collection of operations that have been published.
        /// @return  Collection of operations that have been published, which 
        ///          may be empty.
        virtual const Smp::OperationCollection* GetOperations() const = 0;
    };

}

#endif // SMP_IDYNAMICINVOCATION_H_
