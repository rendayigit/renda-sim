// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/IOperation.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_IOPERATION_H_
#define SMP_IOPERATION_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include "Smp/ICollection.h"
#include "Smp/IParameter.h"
#include "Smp/IRequest.h"
#include "Smp/InvalidOperationName.h"
#include "Smp/InvalidParameterCount.h"
#include "Smp/InvalidParameterType.h"
#include "Smp/PrimitiveTypes.h"
#include "Smp/ViewKind.h"
#include "Smp/IObject.h"

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// This interface describes a published operation.
    class IOperation :
        public virtual Smp::IObject
    {
    public:

        /// Virtual destructor to release memory.
        virtual ~IOperation() noexcept = default;

        /// Provides the collection of parameters that will end-up in the 
        /// request object of CreateRequest(), i.e. all parameter that are not 
        /// of direction return. This collection is ordered the same way as the
        /// parameters in the request object, and may be empty.
        /// The optional return parameter is returned via GetReturnParameter.
        /// @return  Collection of parameters, in the same order as in the 
        ///          request object created by CreateRequest().
        virtual const Smp::ParameterCollection* GetParameters() const = 0;

        /// Return a parameter by name. This works both for parameters in the 
        /// collection of GetParameters(), and for the optional return 
        /// parameter.
        /// @param   name Parameter name.
        /// @return  Parameter object, or null if no parameter with the given 
        ///          name exists.
        virtual Smp::IParameter* GetParameter(
            Smp::String8 name) const = 0;

        /// This operation returns the return parameter, or nullptr if no 
        /// return parameter exists (for a void operation).
        /// @return  The return parameter of the operation, or nullptr for a 
        ///          void operation.
        virtual Smp::IParameter* GetReturnParameter() const = 0;

        /// Provides the view kind of the operation.
        /// @return  View kind of the operation.
        virtual Smp::ViewKind GetView() const = 0;

        /// Return a request object for the operation that describes the 
        /// parameters and the return value.
        /// The request object may be null if the operation does not support 
        /// dynamic invocation.
        /// @return  Request object for operation, or null if the operation 
        ///          does not support dynamic invocation.
        virtual Smp::IRequest* CreateRequest() = 0;

        /// Dynamically invoke the operation using a request object that has 
        /// been created and filled with parameter values by the caller.
        /// @remarks The same request object can be used to invoke an operation
        ///          several times.
        ///          This method raises the InvalidOperationName exception if 
        ///          the request object passed does not name the operation, or 
        ///          if the operation allows no dynamic invocation. When 
        ///          calling invoke with a wrong number of parameters, the 
        ///          InvalidParameterCount exception is raised. When passing a 
        ///          parameter of wrong type, the InvalidParameterType 
        ///          exception is raised.
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
    };

    /// A field collection is an ordered collection of operations, which allows
    /// iterating all members.
    typedef Smp::ICollection<IOperation> OperationCollection;

}

#endif // SMP_IOPERATION_H_
