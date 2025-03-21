// ----------------------------------------------------------------------------
// Origin:    European Cooperation for Space Standardization (ECSS)
// Project:   E-ST-40-07 Simulation Modelling Platform (SMP)
// Platform:  C++
// File:      Smp/PrimitiveTypes.h
// Version:   Issue 1.0 from 28/10/2019
// ----------------------------------------------------------------------------

#ifndef SMP_PRIMITIVETYPES_H_
#define SMP_PRIMITIVETYPES_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include Header Files --------------------------
// ----------------------------------------------------------------------------

#include <array>
#include <climits>
#include <cstdint>
#include <functional>
#include <iosfwd>
#include "Smp/Uuid.h"

#if CHAR_BIT != 8
// In the rare case of a plaform when char != 8, a lot for assumptions are broken
// (e.g. Int8 and UInt8 presence)
#error "This platform does not respect ISO POSIX standard of 8-bit character type."
#endif

// ----------------------------------------------------------------------------
// ------------------------ Types and Interfaces ------------------------------
// ----------------------------------------------------------------------------

/// SMP standard types and interfaces.
namespace Smp
{
    /// 8 bit character type.
    typedef char Char8;

    /// Boolean with true and false.
    typedef bool Bool;

    /// 8 bit signed integer type.
    typedef int8_t Int8;

    /// 8 bit unsigned integer type.
    typedef uint8_t UInt8;

    /// 16 bit signed integer type.
    typedef int16_t Int16;

    /// 16 bit unsigned integer type.
    typedef uint16_t UInt16;

    /// 32 bit signed integer type.
    typedef int32_t Int32;

    /// 32 bit unsigned integer type.
    typedef uint32_t UInt32;

    /// 64 bit signed integer type.
    typedef int64_t Int64;

    /// 64 bit unsigned integer type.
    typedef uint64_t UInt64;

    /// 32-bit single-precision float type.
    typedef float Float32;

    /// 64-bit double-precision float type.
    typedef double Float64;

    /// Duration in nanoseconds.
    /// This type is used for relative time values. It specifies a duration in 
    /// nanoseconds. The following holds for Duration:
    ///      - Duration is a value measured in nanoseconds, which is the lowest
    /// level of granularity supported for time in SMP.
    ///      - Duration is stored as a signed 64-bit integer value.
    ///      - Positive values correspond to positive durations, and negative 
    /// values correspond to negative durations.
    /// This allows specifying duration values roughly between -290 years and 
    /// 290 years. With this definition, the Duration type is compatible with 
    /// the DateTime type.
    typedef int64_t Duration;

    /// Absolute time in nanoseconds.
    /// This type is used for absolute time values. It specifies a time in 
    /// nanoseconds, relative to a reference time. The following holds for 
    /// DateTime:
    ///      - Time is a value measured in nanoseconds, which is the lowest 
    /// level of granularity supported for time in SMP.
    ///      - Time is stored as a signed 64-bit integer value, relative to the
    /// reference time (01.01.2000, 12:00, Modified Julian Date (MJD) 
    /// 2000+0.5).
    ///      - Positive values correspond to times after the reference time, 
    /// and negative values correspond to time values before the reference 
    /// time.
    /// This allows specifying time values roughly between 1710 and 2290. With 
    /// this definition, the DateTime type is compatible with the Duration 
    /// type.
    typedef int64_t DateTime;

    /// 8 bit character string.
    typedef const char* String8;

    /// This is an enumeration of the available primitive types.
    enum class PrimitiveTypeKind : Smp::Int32
    {
        /// No type, e.g. for void.
        PTK_None,

        /// 8 bit character type.
        PTK_Char8,

        /// Boolean with true and false.
        PTK_Bool,

        /// 8 bit signed integer type.
        PTK_Int8,

        /// 8 bit unsigned integer type.
        PTK_UInt8,

        /// 16 bit signed integer type.
        PTK_Int16,

        /// 16 bit unsigned integer type.
        PTK_UInt16,

        /// 32 bit signed integer type.
        PTK_Int32,

        /// 32 bit unsigned integer type.
        PTK_UInt32,

        /// 64 bit signed integer type.
        PTK_Int64,

        /// 64 bit unsigned integer type.
        PTK_UInt64,

        /// 32 bit single-precision floating-point type.
        PTK_Float32,

        /// 64 bit double-precision floating-point type.
        PTK_Float64,

        /// Duration in nanoseconds.
        PTK_Duration,

        /// Absolute time in nanoseconds.
        PTK_DateTime,

        /// 8 bit character string.
        PTK_String8
    };

    /// Stream operator for PrimitiveTypeKind to be able to print an enum value.
    /// @param os Output stream to output to.
    /// @param obj Object to output to stream.
    std::ostream& operator << (std::ostream& os, const PrimitiveTypeKind& obj);

    // ------------------------------------------------------------------------
    // Universal unique identifiers
    // ------------------------------------------------------------------------

    /// Placeholder class with universally unique identifiers of pre-defined SMP types.
    class Uuids
    {
    public:
		/// Unique Identifier of type Uuid.
		static constexpr Uuid Uuid_Uuid = { 0, 0, 0, { ' ',' ',' ',' ','U','u','i','d'} };

        /// Unique Identifier of type Void.
        static constexpr Uuid Uuid_Void     = { 0, 0, 0, { ' ',' ',' ',' ','V','o','i','d'} };

        /// Unique Identifier of type Char8.
        static constexpr Uuid Uuid_Char8    = { 0, 0, 0, { ' ',' ',' ','C','h','a','r','8'} };

        /// Unique Identifier of type Bool.
        static constexpr Uuid Uuid_Bool     = { 0, 0, 0, { ' ',' ',' ',' ','B','o','o','l'} };

        /// Unique Identifier of type Int8.
        static constexpr Uuid Uuid_Int8     = { 0, 0, 0, { ' ',' ',' ',' ','I','n','t','8'} };

        /// Unique Identifier of type UInt8.
        static constexpr Uuid Uuid_UInt8    = { 0, 0, 0, { ' ',' ',' ','U','I','n','t','8'} };

        /// Unique Identifier of type Int16.
        static constexpr Uuid Uuid_Int16    = { 0, 0, 0, { ' ',' ',' ','I','n','t','1','6'} };

        /// Unique Identifier of type UInt16.
        static constexpr Uuid Uuid_UInt16   = { 0, 0, 0, { ' ',' ','U','I','n','t','1','6'} };

        /// Unique Identifier of type Int32.
        static constexpr Uuid Uuid_Int32    = { 0, 0, 0, { ' ',' ',' ','I','n','t','3','2'} };

        /// Unique Identifier of type UInt32.
        static constexpr Uuid Uuid_UInt32   = { 0, 0, 0, { ' ',' ','U','I','n','t','3','2'} };

        /// Unique Identifier of type Int64.
        static constexpr Uuid Uuid_Int64    = { 0, 0, 0, { ' ',' ',' ','I','n','t','6','4'} };

        /// Unique Identifier of type UInt64.
        static constexpr Uuid Uuid_UInt64   = { 0, 0, 0, { ' ',' ','U','I','n','t','6','4'} };

        /// Unique Identifier of type Float32.
        static constexpr Uuid Uuid_Float32  = { 0, 0, 0, { ' ','F','l','o','a','t','3','2'} };

        /// Unique Identifier of type Float64.
        static constexpr Uuid Uuid_Float64  = { 0, 0, 0, { ' ','F','l','o','a','t','6','4'} };

        /// Unique Identifier of type Duration.
        static constexpr Uuid Uuid_Duration = { 0, 0, 0, { 'D','u','r','a','t','i','o','n'} };

        /// Unique Identifier of type DateTime.
        static constexpr Uuid Uuid_DateTime = { 0, 0, 0, { 'D','a','t','e','T','i','m','e'} };

        /// Unique Identifier of type String8.
        static constexpr Uuid Uuid_String8  = { 0, 0, 0, { ' ','S','t','r','i','n','g','8'} };

        /// Unique Identifier of type PrimitiveTypeKind.
        static constexpr Uuid Uuid_PrimitiveTypeKind = {0xd55b0e31, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};

        /// Unique Identifier of type EventId.
        static constexpr Uuid Uuid_EventId = {0xd54589a4, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};

        /// Unique Identifier of type LogMessageKind.
        static constexpr Uuid Uuid_LogMessageKind = {0xd543404f, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};

        /// Unique Identifier of type TimeKind.
        static constexpr Uuid Uuid_TimeKind = {0xd54589a6, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};

        /// Unique Identifier of type ViewKind.
        static constexpr Uuid Uuid_ViewKind = {0xd579e033, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};

        /// Unique Identifier of type ParameterDirectionKind.
        static constexpr Uuid Uuid_ParameterDirectionKind = {0x1b3641ad, 0xf0f0, 0x11dc, 0xb3ae, 0x77a8f1ab4ab6};

        /// Unique Identifier of type ComponentStateKind.
        static constexpr Uuid Uuid_ComponentStateKind = {0xd55d57c7, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};

        /// Unique Identifier of type AccessKind.
        static constexpr Uuid Uuid_AccessKind = {0xe7d5e125, 0xeb8a, 0x11dc, 0x8642, 0xc38618fe0a20};

        /// Unique Identifier of type SimulatorStateKind.
        static constexpr Uuid Uuid_SimulatorStateKind = {0xd56483dc, 0xe618, 0x11dc, 0xab64, 0xbf8df6d7b83a};
    };
}

#endif // SMP_PRIMITIVETYPES_H_
